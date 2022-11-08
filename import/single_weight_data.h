#ifndef SINGLE_WEIGHT_DATA_H
#define SINGLE_WEIGHT_DATA_H

#include <QHash>

class single_weight_data
{
public:
    single_weight_data() {};
    bool set_data(const QString &key, uint value)
    {
        if (value < min || value > max)
            return false;
        int _value = data.value(key, default_value);
        if (_value != default_value)
        {
            weigth_sum += value - _value;
            data.remove(key);
        }
        else
            weigth_sum += value;
        data.insert(key, value);
        return true;
    }
    double get_double(const QString &key) const
    {
        int value = data.value(key, default_value);
        if (value == default_value)
            return default_value;
        else
            return static_cast<double>(value) / weigth_sum;
    }
    int get_int(const QString &key) const
    {
        int value = data.value(key, default_value);
        if (value == default_value)
            return default_value;
        else
            return value;
    }
    int count() const
    {
        return data.count();
    }
    void set_bounds(uint _min, uint _max)
    {
        if (_max > _min)
        {
            max = _max;
            min = _min;
        }
    }
    void set_default_value(double _default)
    {
        default_value = _default;
    }

private:
    QHash<QString, uint> data;
    uint min = 1;
    uint max = 10;
    uint16_t weigth_sum = 0;
    int default_value = -1.;
};

#endif // SINGLE_WEIGHT_DATA_H
