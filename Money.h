#ifndef STUDENT_H
#define STUDENT_H

#include <exception>
#include <iostream>
#include <string>

class Money {
    private:
        // 6 decimals of precision units. E.g: 12.45 = 12450000
        long long units;

        void swap(Money other);

    public:
        Money(const Money &other);
        Money(const Money &&other);
        Money(long long _units);
        Money(std::string _units);
        ~Money();
        
        void mult_per(double per);
        void div_per(double per);
        void set_units(long long units);
        long long get_units();

        Money& operator=(const Money &other) {
            if (&other != this) {
                units = other.units;
            }
            return *this;
        }

        Money& operator=(const Money &&other) {
            if (&other != this) {
                units = other.units;
            }
            return *this;
        }

        bool operator==(const Money &other) const {
            return other.units == units; 
        }

        bool operator!=(const Money &other) const {
            return !(*this == other);
        }

        bool operator>=(const Money &other) const {
            return other.units >= units;
        }

        bool operator<=(const Money &other) const {
            return other.units <= units;
        }

        bool operator>(const Money &other) const {
            return other.units > units; 
        }

        bool operator<(const Money &other) const {
            return other.units < units;
        }

        Money operator+(const Money &other) const {
            Money result(0);
            long long res_units = units + other.units;
            result.units = res_units;
            return result;  
        }

        Money operator-(const Money &other) const {
            Money result(0);
            long long res_units = units - other.units;
            result.units = res_units;
            return result;
        }

        Money operator*(const Money &other) const {
            Money result(0);
            long long res_units = other.units * units;
            result.units = res_units;
            return result;
        }

        Money operator/(const Money &other) const {
            Money result(0);
            long long rem = units;
            long long quo = 0;
            if (other.units > units) {
                result.units = 0;
                return result;
            }

            if (units == other.units) {
                result.units = 1;
                return result;
            }
            
            while (other.units <= rem) {
                rem -= other.units;
                quo++;
            }

            result.units = quo;
            return result;
        }
        
        Money operator/(const int divisor) const {
            Money result(0);
            result.units = units / divisor;
            return result;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Money& money);
};

#endif
