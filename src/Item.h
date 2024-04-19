#import "Rectangle.h"
#import "Coordinate.h"
#import "Bin.h"


class Rectangle : public Item {
    public: 
        Item(int width, int height);
        Bin belongsTo; 
        Coordinate bottomLeft;

        void rotate();

    private:

}