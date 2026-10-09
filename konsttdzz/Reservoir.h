#pragma once
#include <iostream>

enum ReservoirType
{
    Sea,
    Lake,
    River,
    Pond,
    Pool
};

class Reservoir
{
private:
    char* name;
    ReservoirType type;

    double width;
    double length;
    double maxDepth;

public:
    Reservoir();
    explicit Reservoir(const char* name, ReservoirType type,
        double width, double length, double maxDepth);

    Reservoir(const Reservoir& other);
    ~Reservoir();

    void setName(const char* name);
    void setType(ReservoirType type);
    void setWidth(double width);
    void setLength(double length);
    void setMaxDepth(double maxDepth);

    const char* getName() const;
    ReservoirType getType() const;
    double getWidth() const;
    double getLength() const;
    double getMaxDepth() const;

    double getVolume() const;
    double getSurfaceArea() const;

    bool isSameType(const Reservoir& other) const;
    int compareSurfaceArea(const Reservoir& other) const;

    void copyFrom(const Reservoir& other);

    void show() const;

    void saveText(std::ostream& out) const;
    void saveBinary(std::ostream& out) const;
};