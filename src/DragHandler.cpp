
#include "DragHandler.h"

void DragHandler::init(sf::RenderWindow* window_, sf::Event* event_) {
    m_window = window_;
    m_event  = event_;
    m_dragging = false;

    // vectors
    m_deltaPos_total = { 0, 0 };
    m_deltaPos       = { 0, 0 };

    // rectangle
    m_draggedRect.setFillColor(sf::Color(170,215,230, 200));    // light blue
}


void DragHandler::updateDragging() {
    // filter out non-left & non-middle clicks
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_dragging = false;
        return;
    }

    const sf::Vector2i current_mouse = static_cast<sf::Vector2i>(
            m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)));

    // when first clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
        && m_event->type == sf::Event::MouseButtonPressed)
    {
        // set origin coords

        m_orig_Pos = current_mouse;
        m_prev_Pos = m_orig_Pos;

        m_dragging = true;

        // recreate new rectangle
        m_draggedRect.setPosition(static_cast<sf::Vector2f>(m_orig_Pos));
    }

    // if dragging
    if (m_event->type = sf::Event::MouseMoved)
    {
        // update total change
        m_deltaPos_total = current_mouse - m_orig_Pos;

        // update change
        m_deltaPos = current_mouse - m_prev_Pos;
        m_prev_Pos = current_mouse;

        // for left-click drags only
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            // update rectangle size - independent of the current view's zoom
            //m_draggedRect.setSize(m_window->mapPixelToCoords(m_deltaPos_total));
            m_draggedRect.setSize(static_cast<sf::Vector2f>(
                    m_window->mapCoordsToPixel(
                            m_window->mapPixelToCoords(m_deltaPos_total))));    //testing
    }
    else
        m_deltaPos = { 0, 0 };  // no change in mouse pos

}

const sf::RectangleShape &DragHandler::getDraggedRectangle() {
    return m_draggedRect;
}

const sf::Vector2i &DragHandler::getDeltaPos() {
    return m_deltaPos;
}

bool DragHandler::isDragging() {
    return m_dragging;
}

const sf::Vector2i &DragHandler::getOriginPos() {
    return m_orig_Pos;
}

const sf::Vector2i &DragHandler::getDeltaTotalPos() {
    return m_deltaPos_total;
}

