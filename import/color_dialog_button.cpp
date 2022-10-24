#include "color_dialog_button.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>

color_dialog_button::color_dialog_button (QColor color, QWidget *parent) : QWidget (parent)
{
  m_color = color;
  setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QColor color_dialog_button::color () const
{
  return m_color;
}

void color_dialog_button::set_color (const QColor &color)
{
  m_color = color;
  update ();
}

void color_dialog_button::set_default_color (const QColor &color)
{
  m_default_color = color;
  update ();
}

void color_dialog_button::set_custom_select_function (select_function_t select_function)
{
  m_custom_select_function = std::move (select_function);
}

void color_dialog_button::mousePressEvent (QMouseEvent *qevent)
{
  if (qevent->button () != Qt::LeftButton)
    return;

QColorDialog::ColorDialogOptions options;
#ifndef _WIN32
options |= QColorDialog::DontUseNativeDialog;
#endif

  QColor new_color;

  if (m_custom_select_function)
    {
      new_color = m_custom_select_function (m_color);
    }
  else
    {
      new_color = QColorDialog::getColor (m_color, this, {}, options);
    }

  if (!new_color.isValid ())
    return;

  set_color (new_color);

  Q_EMIT color_changed (new_color);
}

void color_dialog_button::paintEvent (QPaintEvent * /*qevent*/)
{
  QPainter painter (this);
  painter.setRenderHints (QPainter::Antialiasing, true);

  if (!m_color.isValid () && !m_default_color.isValid ())
    draw_unknown_color_sign (painter);

  if (m_color.isValid ())
    painter.setBrush (m_color);
  else if (m_default_color.isValid ())
    painter.setBrush (m_default_color);
  else
    painter.setBrush (Qt::NoBrush);

  painter.setPen (QPen (Qt::gray, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
  draw_rect (painter);

  if (!isEnabled ())
    {
      QRadialGradient grad (0.25, 0.25, 1.0);
      grad.setCoordinateMode (QGradient::ObjectBoundingMode);
      grad.setColorAt (0.0, Qt::gray);
      grad.setColorAt (1.0, Qt::transparent);
      painter.setBrush (grad);
      draw_rect (painter);
    }
}

QSize color_dialog_button::sizeHint () const { return QSize (32, 24); }

void color_dialog_button::draw_unknown_color_sign (QPainter &painter)
{
  painter.setBrush (Qt::lightGray);
  painter.setPen (Qt::NoPen);
  draw_rect (painter);

  painter.setPen (Qt::black);
  painter.setBrush (Qt::NoBrush);
  QFont font;
  font.setPixelSize (24);
  painter.setFont (font);
  painter.drawText (rect (), Qt::AlignCenter, "?");
}

void color_dialog_button::draw_rect (QPainter &painter)
{
    constexpr int radius = 3;
    painter.drawRoundedRect (rect ().adjusted (0, 0, -1, -1), radius, radius);
}
