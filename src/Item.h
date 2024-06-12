// Item.h

#pragma once
#include "Rectangle.h"
#include "Coordinate.h"
#include <ostream>
#include <functional> // inclure <functional> pour utiliser std::hash

class Item : public Rectangle {
public: 
    Item(int id, int width, int height);
    Coordinate topLeft;
    int m_id; 
    void rotate();

    friend std::ostream &operator<<(std::ostream &out, const Item& i);
    void serialize(std::ofstream& outputFile) const;

private:
};

// Spécialisation de std::hash pour la classe Item pour que ce soit compatible avec std::unordered_map
namespace std {
    template<> struct hash<Item> {
        size_t operator()(const Item& item) const {
            size_t hashWidth = hash<int>()(item.getWidth());
            size_t hashHeight = hash<int>()(item.getHeight());
            size_t hashId = hash<int>()(item.m_id);
            return hashWidth ^ (hashHeight << 1) ^ (hashId << 2);
        }
    };
}

// Opérateur d'égalité pour la classe Item
inline bool operator==(const Item& lhs, const Item& rhs) {
    return lhs.getHeight() == rhs.getHeight() && lhs.getWidth() == rhs.getWidth() && lhs.m_id == rhs.m_id;
}
