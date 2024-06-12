
#ifndef PHYSICS_DEMO_DRAGHANDLER_H
#define PHYSICS_DEMO_DRAGHANDLER_H

#include <SFML/Graphics.hpp>


class DragHandler {
public:

    static void init(sf::RenderWindow*, sf::Event*);
    static void updateDragging();
    static bool isDragging();

    // return rectangle where mouse is currently dragged
    static const sf::RectangleShape& getDraggedRectangle();

    ///////////////////////////
    //// useful vector returns
    ///////////////////////////

    // return change in mouse coords - only for current mouse drag
    // will reset once dragging is re-invoked
    static const sf::Vector2i&       getDeltaPos();
    static const sf::Vector2i&       getDeltaTotalPos();
    static const sf::Vector2i&       getOriginPos();

private:
    inline static sf::RectangleShape m_draggedRect = sf::RectangleShape(sf::Vector2f (0.f, 0.f));
    inline static sf::Vector2i       m_orig_Pos;
    inline static sf::Vector2i       m_prev_Pos;
    inline static sf::Vector2i       m_deltaPos;
    inline static sf::Vector2i       m_deltaPos_total;

    inline static bool               m_dragging;

    // main program variables - statically allocated
    inline static sf::RenderWindow*    m_window;
    inline static sf::Event*           m_event;
};


#endif //PHYSICS_DEMO_DRAGHANDLER_H
