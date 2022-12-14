#pragma once

#include <QString>
#include <QList>
#include <QVariant>

enum class j_property_id
{
    WORDS_IN_MESSAGE,
    SYMBOLS_IN_WORD,

    COUNT
};

const QString enum_to_string(j_property_id id);

class j_abstract_property
{
public:
    j_abstract_property(j_property_id _id) : id(_id) {};
    ~j_abstract_property() = default;

    virtual bool is_simple() = 0;
    virtual bool is_empty() = 0;
    virtual double correlation(j_abstract_property* another) = 0;
    virtual bool join(j_abstract_property* another) = 0;
    j_property_id id_enum() const { return id; }
    int id_int() const { return static_cast<int>(id); }
    const QString id_string() const { return enum_to_string(id); }
    uint32_t weight() const { return count; }

    void set_weight(uint32_t w) { count = w; }

    static bool can_be_merged(j_abstract_property* first, j_abstract_property* second)
    {
        if (first && second)
            return (first->id_enum() == second->id_enum() || first->is_empty());
        else
            return false;
    }

private:
    j_property_id id;
    uint32_t count = 0;
};

class j_simple_property final: public j_abstract_property
{
public:
    j_simple_property(j_property_id _id) : j_abstract_property(_id) {}
    j_simple_property(const j_simple_property &another);
    ~j_simple_property() = default;

    virtual bool is_simple() override { return true; }
    virtual bool is_empty() override { return (value < 0); }
    virtual double correlation(j_abstract_property* another) override;
    virtual bool join(j_abstract_property* another) override;
    double data() const { return value; }
    void set_data(double val)
    {
        if (val >= 0.)
            value = val;
    }

private:
    double value = -1.;
};
