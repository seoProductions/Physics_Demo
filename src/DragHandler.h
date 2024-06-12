
#ifndef PHYSICS_DEMO_DRAGHANDLER_H
#define PHYSICS_DEMO_DRAGHANDLER_H

#include <SFML/Graphics.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////    Drag handler currently supports Dragging and Selecting
////    Info on dragging is returned as bool values or sf::Vector's
////
////    Only Left and Middle - Clicks - are recognized for dragging events
////
////    Left-Click      drag supports selecting and dragging
////    Middle-Click    drag does not support selecting; neither does it update the drawable selecting rectangle
////
////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DragHandler {
public:

    static void init(sf::RenderWindow*, sf::Event*);
    static void updateDragging();

    static bool isDragging();
    static bool isSelecting();

    // return rectangle where mouse is currently dragged
    static const sf::RectangleShape& getDraggedRectangle();

    ///////////////////////////
    //// useful vector returns
    ///////////////////////////

    // return change in mouse coords - only for current mouse drag
    // will reset once dragging is re-invoked
    static const sf::Vector2i&       getDeltaPos ();
    static const sf::Vector2f&       getDeltaPosf();
    static const sf::Vector2i&       getDeltaTotalPos();
    static const sf::Vector2i&       getOriginPos();

private:
    inline static sf::RectangleShape m_draggedRect = sf::RectangleShape(sf::Vector2f (0.f, 0.f));
    inline static sf::Vector2i       m_orig_Pos;
    inline static sf::Vector2i       m_prev_Pos;
    inline static sf::Vector2i       m_deltaPos;
    inline static sf::Vector2i       m_deltaPos_total;

    inline static bool               m_dragging;
    inline static bool               m_selecting;

    // main program variables - statically allocated
    inline static sf::RenderWindow*    m_window;
    inline static sf::Event*           m_event;
};


#endif //PHYSICS_DEMO_DRAGHANDLER_H
