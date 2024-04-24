#import "Rectangle.h"
#import "Coordinate.h"
#import "Bin.h"


class Item : public Rectangle {
    public: 
        Item(int width, int height);
        Bin *belongsTo; 
        Coordinate bottomLeft;

        void rotate();

    private:

};