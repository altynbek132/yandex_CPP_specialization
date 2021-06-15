#include <bits/stdc++.h>
#include <ostream>
#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

pair<Point, Point> GetConstraints(const Point& start, const Size& size, const Image& image) {
    Point begin{max(0, min(start.x, static_cast<int>(image[0].size() - 1))),  //
                max(0, min(start.y, static_cast<int>(image.size() - 1)))};
    Point end{max(0, min(start.x + size.width, static_cast<int>(image[0].size()))),  //
              max(0, min(start.y + size.height, static_cast<int>(image.size())))};
    return {begin, end};
}

class Figure : public IShape {
   public:
    Figure() = default;
    Figure(shared_ptr<ITexture> texture, Point point, Size size)
        : texture_(move(texture)), point_(point), size_(size) {}

    void SetPosition(Point point) override { point_ = point; }
    Point GetPosition() const override { return point_; }
    void SetSize(Size size) override { size_ = size; }
    Size GetSize() const override { return size_; }
    void SetTexture(std::shared_ptr<ITexture> ptr) override { texture_ = move(ptr); }
    ITexture* GetTexture() const override { return texture_.get(); }

   protected:
    shared_ptr<ITexture> texture_;
    Point point_{0, 0};
    Size size_{0, 0};

    void DrawFromTextureToImage(int y, int x, Image& image) const {
        if (!texture_) {
            image[y][x] = '.';
            return;
        }

        const Size& image_size = texture_->GetSize();
        if (y < point_.y + image_size.height && x < point_.x + image_size.width) {
            image[y][x] = texture_->GetImage()[y - point_.y][x - point_.x];
        } else {
            image[y][x] = '.';
        }
    }

   public:
#ifdef MASLO
    friend ostream& operator<<(ostream& os, const Figure& figure) {
        if (!figure.texture_) {
            os << " texture_: no texture";
        } else {
            os << " texture_: " << *figure.texture_;
        }

        os                                   //
            << " point_: " << figure.point_  //
            << " size_: " << figure.size_;
        return os;
    }
#endif  // MASLO
};

class Rectangle : public Figure {
   public:
    Rectangle() = default;
    Rectangle(shared_ptr<ITexture> texture, Point point, Size size) : Figure(move(texture), point, size) {}
    unique_ptr<IShape> Clone() const override { return std::make_unique<Rectangle>(texture_, point_, size_); }

    void Draw(Image& image) const override {
        auto [begin, end] = GetConstraints(point_, size_, image);
        for (int y = begin.y; y < end.y; ++y) {
            for (int x = begin.x; x < end.x; ++x) {
                DrawFromTextureToImage(y, x, image);
            }
        }
    }
};

class Ellipse : public Figure {
   public:
    Ellipse() = default;
    Ellipse(shared_ptr<ITexture> texture, Point point, Size size) : Figure(move(texture), point, size) {}
    unique_ptr<IShape> Clone() const override { return std::make_unique<Ellipse>(texture_, point_, size_); }

    void Draw(Image& image) const override {
        auto [begin, end] = GetConstraints(point_, size_, image);
        for (int y = begin.y; y < end.y; ++y) {
            for (int x = begin.x; x < end.x; ++x) {
                if (!IsPointInEllipse({x - point_.x, y - point_.y}, size_)) {
                    continue;
                }
                DrawFromTextureToImage(y, x, image);
            }
        }
    }
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Rectangle: {
            return make_unique<Rectangle>();
        }
        case ShapeType::Ellipse: {
            return make_unique<Ellipse>();
        }
        default:
            throw runtime_error("chotam?");
    }
}

#ifdef MASLO
ostream& operator<<(ostream& os, const Point& point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
ostream& operator<<(ostream& os, const Size& size) {
    os << "width: " << size.width << " height: " << size.height;
    return os;
}
ostream& operator<<(ostream& os, const ITexture& texture) {
    os << texture.GetSize();
    return os;
}
#endif  // MASLO
