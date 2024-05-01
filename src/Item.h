#import "Rectangle.h"
#import "Coordinate.h"
#import "Bin.h"


class Item : public Rectangle {
    public: 
        Item(int width, int height, int id);
        Bin *belongsTo; 
        Coordinate topLeft;
        int m_id; 

        void rotate();

    private:

};