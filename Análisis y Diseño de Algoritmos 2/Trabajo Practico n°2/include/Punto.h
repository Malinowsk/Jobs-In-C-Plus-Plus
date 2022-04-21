#ifndef PUNTO_H
#define PUNTO_H

class Punto {
public:
    Punto(int x, int y) { this->x = x; this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    bool operator < (const Punto & p) const {
            if (x < p.x) { return true; }
            else if (x > p.x) { return false; }
            else { return y < p.y; } }
    bool operator = (const Punto & p) const{
        if ((x == p.x) && ( y == p.y))
            return true;
        return false;
    }
    bool operator != (const Punto & p) const{
        if ((x == p.x) && ( y == p.y))
            return false;
        return true;
    }
private:
    int x, y;
};

#endif // PUNTO_H
