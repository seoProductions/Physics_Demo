
#include "DragHandler.hpp"

/////////////////////////////////////
////
////    DragHandler Implementation
////
/////////////////////////////////////


void DragHandler::init(sf::RenderWindow* window_, sf::Event* event_) {
    m_window = window_;
    m_event  = event_;
    m_dragging  = false;
    m_selecting = false;

    m_needs_reset = false;
    resetVectors();

    // rectangle
    m_draggedRect.setFillColor(sf::Color(150,200,210, 180));    // light blue
}


void DragHandler::updateDragging()
{
    // filter out non-left & non-middle clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))    m_selecting = true;
    else
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))  m_selecting = false;
    else
    {
        if (m_needs_reset) resetVectors();
        return;
    }
    // Mouse has been engaged. Proceed to logic
    m_needs_reset = true;

    // obtain mouse pos
    const sf::Vector2i current_mouse =  static_cast<sf::Vector2i>(
            m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)));     // align with current view

    // when first clicked
    if (m_event->type == sf::Event::MouseButtonPressed)
    {
        // set origin coords
        m_orig_Pos = current_mouse;
        m_prev_Pos = m_orig_Pos;

        m_dragging = true;

        // re-position rectangle
        m_draggedRect.setPosition(static_cast<sf::Vector2f>(m_orig_Pos));
    }

    // if dragging
    if (m_event->type == sf::Event::MouseMoved)
    {
        // update total change
        m_deltaPos_total = current_mouse - m_orig_Pos;

        // update change
        m_deltaPos = current_mouse - m_prev_Pos;
        m_prev_Pos = current_mouse;

        // for left-click drags only
         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            // update rectangle size - independent of the current view's zoom
            m_draggedRect.setSize(static_cast<sf::Vector2f>(
                    m_window->mapCoordsToPixel(
                    m_window->mapPixelToCoords(m_deltaPos_total))));        // translate to pixel coords
    }
    else
        m_deltaPos = { 0, 0 };  // no change in mouse pos

}

////////////////////
////
////    Getter's
////
////////////////////

const sf::RectangleShape &DragHandler::getDraggedRectangle() {
    return m_draggedRect;
}

const sf::Vector2i &DragHandler::getDeltaPos() {
    return m_deltaPos;
}

bool DragHandler::isDragging() {
    return m_dragging;
}


const sf::Vector2i &DragHandler::getDeltaTotalPos() {
    return m_deltaPos_total;
}

bool DragHandler::isSelecting() {
    return m_selecting;
}

// will return copy, the negation here is done to match the world view coordinates & grid view coordinates
const sf::Vector2f DragHandler::getDeltaPosLocal() {
    return -static_cast<sf::Vector2f>(
            m_window->mapCoordsToPixel(
            m_window->mapPixelToCoords(DragHandler::getDeltaPos())));
}

void DragHandler::resetVectors() {
    m_needs_reset = false;
    m_dragging  = false;
    m_selecting = false;
    m_draggedRect.setSize( sf::Vector2f ( 0, 0 ));
    m_prev_Pos          = { 0, 0 };
    m_deltaPos          = { 0, 0 };
    m_deltaPos_total    = { 0, 0 };
}



