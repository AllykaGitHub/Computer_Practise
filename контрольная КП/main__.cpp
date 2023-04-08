#include <iostream>
#include <string>

// Абстрактный базовый класс для геометрических фигур
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
};

// Конкретный класс круга
class Circle : public Shape {
public:
    void draw() override {
        // реализация отображения круга
        std::cout << "Drawing Circle" << std::endl;
    }
};

// Конкретный класс прямоугольника
class Rectangle : public Shape {
public:
    void draw() override {
        // реализация отображения прямоугольника
        std::cout << "Drawing Rectangle" << std::endl;
    }
};

// Конкретный класс многоугольника
class Polygon : public Shape {
public:
    void draw() override {
        // реализация отображения многоугольника
        std::cout << "Drawing Polygon" << std::endl;
    }
};

// Абстрактный класс для рендерера
class ShapeRenderer {
public:
    virtual ~ShapeRenderer() {}
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
    virtual void drawPixel(int x, int y) = 0;
    virtual void drawShape(Shape& shape) = 0;
};

// Конкретный класс рендерера для экрана
class ScreenRenderer : public ShapeRenderer {
public:
    void drawLine(int x1, int y1, int x2, int y2) override {
        // реализация отображения линии на экране
        std::cout << "Drawing line on screen from (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;
    }
    void drawPixel(int x, int y) override {
        // реализация отображения пикселя на экране
        std::cout << "Drawing pixel on screen at (" << x << "," << y << ")" << std::endl;
    }
    void drawShape(Shape& shape) override {
        // вызов метода draw() для переданной фигуры
        shape.draw();
    }
};

// Конкретный класс рендерера для принтера
class PrinterRenderer : public ShapeRenderer {
public:
    void drawLine(int x1, int y1, int x2, int y2) override {
        // реализация печати линии на принтере
        std::cout << "Printing line from (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;
    }
    void drawPixel(int x, int y) override {
        // реализация печати пикселя на принтере
        std::cout << "Printing pixel at (" << x << "," << y << ")" << std::endl;
    }
    void drawShape(Shape& shape) override {
        // вызов метода draw() для переданной фигуры
        shape.draw();
    }
};

// Конкретный класс для формата вывода XML
class XmlWriter {
public:
    void writeXmlStart() {
        std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
}
void writeStartElement(const std::string& elementName) {
std::cout << "<" << elementName << ">" << std::endl;
}
void writeEndElement(const std::string& elementName) {
std::cout << "</" << elementName << ">" << std::endl;
}
};

int main() {
// Создаем экземпляры фигур
Circle circle;
Rectangle rectangle;
Polygon polygon;

// Создаем экземпляры рендереров
ScreenRenderer screenRenderer;
PrinterRenderer printerRenderer;

// Отображаем фигуры на экране
screenRenderer.drawShape(circle);
screenRenderer.drawShape(rectangle);
screenRenderer.drawShape(polygon);

// Печатаем фигуры на принтере
printerRenderer.drawShape(circle);
printerRenderer.drawShape(rectangle);
printerRenderer.drawShape(polygon);

// Записываем информацию о фигурах в формате XML
XmlWriter xmlWriter;
xmlWriter.writeXmlStart();
xmlWriter.writeStartElement("Shapes");
xmlWriter.writeStartElement("Circle");
xmlWriter.writeEndElement("Circle");
xmlWriter.writeStartElement("Rectangle");
xmlWriter.writeEndElement("Rectangle");
xmlWriter.writeStartElement("Polygon");
xmlWriter.writeEndElement("Polygon");
xmlWriter.writeEndElement("Shapes");

return 0;
}