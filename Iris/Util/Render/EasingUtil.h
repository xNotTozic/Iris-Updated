#pragma once

class EasingUtil {
public:
    __forceinline double linear() {
        return this->percentage;
    }
    __forceinline double easeInSine() {
        return sin(1.5707963 * this->percentage);
    }
    __forceinline double easeOutSine() {
        return 1 + sin(1.5707963 * (--this->percentage));
    }
    __forceinline double easeInOutSine() {
        return 0.5 * (1 + sin(3.1415926 * (this->percentage - 0.5)));
    }
    __forceinline double easeInQuad() {
        return this->percentage * this->percentage;
    }
    __forceinline double easeOutQuad() {
        return this->percentage * (2 - this->percentage);
    }
    __forceinline double easeInOutQuad() {
        return this->percentage < 0.5 ? 2 * this->percentage * this->percentage : this->percentage * (4 - 2 * this->percentage) - 1;
    }
    __forceinline double easeInCubic() {
        return this->percentage * this->percentage * this->percentage;
    }
    __forceinline double easeOutCubic() {
        return 1 + (--this->percentage) * this->percentage * this->percentage;
    }
    __forceinline double easeInOutCubic() {
        return this->percentage < 0.5 ? 4 * this->percentage * this->percentage * this->percentage : 1 + (--this->percentage) * (2 * (--this->percentage)) * (2 * this->percentage);
    }
    __forceinline double easeInQuart() {
        this->percentage *= this->percentage;
        return this->percentage * this->percentage;
    }
    __forceinline double easeOutQuart() {
        this->percentage = (--this->percentage) * this->percentage;
        return 1 - this->percentage * this->percentage;
    }
    __forceinline double easeInOutQuart() {
        if (this->percentage < 0.5) {
            this->percentage *= this->percentage;
            return 8 * this->percentage * this->percentage;
        }
        else {
            this->percentage = (--this->percentage) * this->percentage;
            return 1 - 8 * this->percentage * this->percentage;
        }
    }
    __forceinline double easeInQuint() {
        double t2 = this->percentage * this->percentage;
        return this->percentage * t2 * t2;
    }
    __forceinline double easeOutQuint() {
        double t2 = (--this->percentage) * this->percentage;
        return 1 + this->percentage * t2 * t2;
    }
    __forceinline double easeInOutQuint() {
        double t2;
        if (this->percentage < 0.5) {
            t2 = this->percentage * this->percentage;
            return 16 * this->percentage * t2 * t2;
        }
        else {
            t2 = (--this->percentage) * this->percentage;
            return 1 + 16 * this->percentage * t2 * t2;
        }
    }
    __forceinline double easeInExpo() {
        return (pow(2, 8 * this->percentage) - 1) / 255;
    }
    __forceinline double easeOutExpo() {
        return 1 - pow(2, -8 * this->percentage);
    }
    __forceinline double easeInOutExpo() {
        if (this->percentage < 0.5) {
            return (pow(2, 16 * this->percentage) - 1) / 510;
        }
        else {
            return 1 - 0.5 * pow(2, -16 * (this->percentage - 0.5));
        }
    }
    __forceinline double easeInCirc() {
        return 1 - sqrt(1 - this->percentage);
    }
    __forceinline double easeOutCirc() {
        return sqrt(this->percentage);
    }
    __forceinline double easeInOutCirc() {
        if (this->percentage < 0.5) {
            return (1 - sqrt(1 - 2 * this->percentage)) * 0.5;
        }
        else {
            return (1 + sqrt(2 * this->percentage - 1)) * 0.5;
        }
    }
    __forceinline double easeInBack() {
        return this->percentage * this->percentage * (2.70158 * this->percentage - 1.70158);
    }
    __forceinline double easeOutBack() {
        const double c1 = 1.70158;
        const double c3 = c1 + 1;

        return 1 + c3 * pow(this->percentage - 1, 3) + c1 * pow(this->percentage - 1, 2);
    }
    __forceinline double easeInOutBack() {
        const double c1 = 1.70158;
        const double c2 = c1 * 1.525;

        return this->percentage < 0.5
            ? (pow(2 * this->percentage, 2) * ((c2 + 1) * 2 * this->percentage - c2)) / 2
            : (pow(2 * this->percentage - 2, 2) * ((c2 + 1) * (this->percentage * 2 - 2) + c2) + 2) / 2;
    }
    __forceinline double easeInElastic() {
        double t2 = this->percentage * this->percentage;
        return t2 * t2 * sin(this->percentage * PI * 4.5);
    }
    __forceinline double easeOutElastic() {
        double t2 = (this->percentage - 1) * (this->percentage - 1);
        return 1 - t2 * t2 * cos(this->percentage * PI * 4.5);
    }
    __forceinline double easeInOutElastic() {
        double t2;
        if (this->percentage < 0.45) {
            t2 = this->percentage * this->percentage;
            return 8 * t2 * t2 * sin(this->percentage * PI * 9);
        }
        else if (this->percentage < 0.55) {
            return 0.5 + 0.75 * sin(this->percentage * PI * 4);
        }
        else {
            t2 = (this->percentage - 1) * (this->percentage - 1);
            return 1 - 8 * t2 * t2 * sin(this->percentage * PI * 9);
        }
    }
    __forceinline double easeInBounce() {
        return pow(2, 6 * (this->percentage - 1)) * abs(sin(this->percentage * PI * 3.5));
    }
    __forceinline double easeOutBounce() {
        return 1 - pow(2, -6 * this->percentage) * abs(cos(this->percentage * PI * 3.5));
    }
    __forceinline double easeInOutBounce() {
        if (this->percentage < 0.5) {
            return 8 * pow(2, 8 * (this->percentage - 1)) * abs(sin(this->percentage * PI * 7));
        }
        else {
            return 1 - 8 * pow(2, -8 * this->percentage) * abs(sin(this->percentage * PI * 7));
        }
    }

    float percentage;

    EasingUtil() {
        this->percentage = 0.0f;
    };

    __forceinline void resetPercentage() {
        this->percentage = 0.0f;
    }

    __forceinline bool isPercentageMax() {
        return this->percentage >= 1.f;
    }

    __forceinline bool isPercentageMin() {
        return this->percentage <= 0.f;
    }

    __forceinline void incrementPercentage(float value) {
        this->percentage += value;
        if (this->isPercentageMax()) this->percentage = 1.f;
    }

    __forceinline void decrementPercentage(float value) {
        this->percentage -= value;
        if (this->isPercentageMin()) this->percentage = 0.f;
    }
};
