#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>

class GasCylinder {
public:
    GasCylinder(double volume, double mass, double molar) :
            volume_(volume), mass_(mass), molar_(molar) {}

    double GetPressure(int T) const {
        const double R = 8.314462618; // универсальная газовая постоянная
        const double p = mass_ / molar_ * R * T / volume_; // уравнение состояния идеального газа
        return p;
    }

    double AmountOfMatter() const {
        const double N = mass_ / molar_; // количество вещества
        return N;
    }

    void ModifMass(double dm) {
        mass_ += dm;
    }

    void ModifVolume(double dV) {
        volume_ += dV;
    }

    double CalculateDp(int TO, int dT) {
        const double p1 = GetPressure(TO);
        const double p2 = GetPressure(TO + dT);
        const double dp = std::abs(p2 - p1); // изменение давления
        return dp;
    }

    std::string ToString() const {
        std::ostringstream oss;
        oss << "Volume: " << volume_ << " m3, "
            << "Mass: " << mass_ << " kg, "
            << "Molar: " << molar_ << " kg/mol";
        return oss.str();
    }

    std::string GetData() const {
        return ToString();
    }

private:
    double volume_; // объём баллона, м3
    double mass_; // масса газа, кг
    double molar_; // молярная масса газа, кг/моль
};



int main() {
 
}

