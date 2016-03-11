struct Ponto{
    float x;
    float y;

    Ponto operator+(const Ponto& rhs) const{
        return {x + rhs.x,y + rhs.y};
    }

    Ponto operator+=(const Ponto& rhs){
        x += rhs.x;
        y += rhs.y;

        return {x,y};
    }

    Ponto operator-(const Ponto& rhs) const{
        return {x - rhs.x,y - rhs.y};
    }

    Ponto operator-=(const Ponto& rhs){
        x -= rhs.x;
        y -= rhs.y;

        return {x,y};
    }

    bool operator==(const Ponto& rhs) const{
        return (x == rhs.x && y == rhs.y);
    }

    bool operator!=(const Ponto& rhs) const{
        return !(x == rhs.x && y == rhs.y);
    }

    Ponto operator=(const Ponto& rhs){
        x = rhs.x;
        y = rhs.y;

        return {x,y};
    }
};
