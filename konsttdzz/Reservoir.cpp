#include "Reservoir.h"
#include <cstring>

Reservoir::Reservoir()
{
    name = nullptr;
    type = Lake;
    width = 0;
    length = 0;
    maxDepth = 0;
}

Reservoir::Reservoir(const char* name, ReservoirType type,
    double width, double length, double maxDepth)
{
    this->name = nullptr;
    setName(name);

    this->type = type;
    this->width = width;
    this->length = length;
    this->maxDepth = maxDepth;
}

Reservoir::Reservoir(const Reservoir& other)
{
    name = nullptr;
    copyFrom(other);
}

Reservoir::~Reservoir()
{
    delete[] name;
}

void Reservoir::setName(const char* name)
{
    delete[] this->name;

    if (name != nullptr)
    {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);
    }
    else
    {
        this->name = nullptr;
    }
}

void Reservoir::setType(ReservoirType type)
{
    this->type = type;
}

void Reservoir::setWidth(double width)
{
    this->width = width;
}

void Reservoir::setLength(double length)
{
    this->length = length;
}

void Reservoir::setMaxDepth(double maxDepth)
{
    this->maxDepth = maxDepth;
}

const char* Reservoir::getName() const
{
    return name;
}

ReservoirType Reservoir::getType() const
{
    return type;
}

double Reservoir::getWidth() const
{
    return width;
}

double Reservoir::getLength() const
{
    return length;
}

double Reservoir::getMaxDepth() const
{
    return maxDepth;
}

double Reservoir::getVolume() const
{
    return width * length * maxDepth;
}

double Reservoir::getSurfaceArea() const
{
    return width * length;
}

bool Reservoir::isSameType(const Reservoir& other) const
{
    return type == other.type;
}

int Reservoir::compareSurfaceArea(const Reservoir& other) const
{
    if (!isSameType(other))
        return 0;

    if (getSurfaceArea() > other.getSurfaceArea())
        return 1;

    if (getSurfaceArea() < other.getSurfaceArea())
        return -1;

    return 0;
}

void Reservoir::copyFrom(const Reservoir& other)
{
    setName(other.name);

    type = other.type;
    width = other.width;
    length = other.length;
    maxDepth = other.maxDepth;
}

void Reservoir::show() const
{
    std::cout << "Название: ";

    if (name != nullptr)
        std::cout << name;
    else
        std::cout << "Нет";

    std::cout << "\n";

    std::cout << "Тип: ";

    switch (type)
    {
    case Sea:
        std::cout << "Море";
        break;

    case Lake:
        std::cout << "Озеро";
        break;

    case River:
        std::cout << "Река";
        break;

    case Pond:
        std::cout << "Пруд";
        break;

    case Pool:
        std::cout << "Бассейн";
        break;
    }

    std::cout << "\n";
    std::cout << "Ширина: " << width << "\n";
    std::cout << "Длина: " << length << "\n";
    std::cout << "Максимальная глубина: " << maxDepth << "\n";
    std::cout << "Объем: " << getVolume() << "\n";
    std::cout << "Площадь поверхности: " << getSurfaceArea() << "\n";
}

void Reservoir::saveText(std::ostream& out) const
{
    out << "Название: " << name << "\n";
    out << "Тип: " << type << "\n";
    out << "Ширина: " << width << "\n";
    out << "Длина: " << length << "\n";
    out << "Максимальная глубина: " << maxDepth << "\n";
    out << "Объем: " << getVolume() << "\n";
    out << "Площадь поверхности: " << getSurfaceArea() << "\n";
}

void Reservoir::saveBinary(std::ostream& out) const
{
    int nameLength = name ? strlen(name) : 0; //бинарный файл

    out.write((char*)&nameLength, sizeof(nameLength));

    if (nameLength > 0)
        out.write(name, nameLength);

    out.write((char*)&type, sizeof(type));
    out.write((char*)&width, sizeof(width));
    out.write((char*)&length, sizeof(length));
    out.write((char*)&maxDepth, sizeof(maxDepth));
}