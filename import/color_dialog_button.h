#pragma once

#include <QColor>
#include <QWidget>

class color_dialog_button : public QWidget
{
  using select_function_t = std::function<QColor (const QColor&)>;

  Q_OBJECT

  QColor m_color;
  QColor m_default_color;
  select_function_t m_custom_select_function;

public:
  color_dialog_button (QColor color = QColor (), QWidget *parent = nullptr);
  QColor color () const;
  void set_color (const QColor &color);
  // sets default color which will be shown if invalid color is set
  // nothing was set or default_color is invalid, question mark will be shown.
  void set_default_color (const QColor &color);

  // custom function instead of calling QColorDialog::getColor
  // for example creating another type dialog
  void set_custom_select_function (select_function_t select_function);

protected:
  virtual void mousePressEvent (QMouseEvent *qevent) override;
  virtual void paintEvent (QPaintEvent *qevent) override;
  virtual QSize sizeHint () const override;

Q_SIGNALS:
  void color_changed (QColor);

private:
  void draw_unknown_color_sign (QPainter &painter);
  void draw_rect (QPainter &painter);
};
