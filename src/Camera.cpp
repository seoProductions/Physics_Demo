
#include "Camera.hpp"
#include "GridSpace.hpp"

Camera::Camera() {
    m_target_size = m_view.getSize();
    m_is_updating_scale = false;
    m_is_updating_size  = false;
}


void Camera::updateSize() {
    if (!m_is_updating_size)                return;
    if (m_target_size == m_view.getSize())  return;
    if (Time::getDeltaTime() > 1)           // for intense lag
    {
        m_view.setSize(m_target_size);
        return;
    }

    m_target_size.x = clamp(m_target_size.x, m_min_size.x, m_max_size.x);
    m_target_size.y = clamp(m_target_size.y, m_min_size.y, m_max_size.y);

    // quick check for negligible difference
    const auto deltaSize = m_target_size - m_view.getSize();

    constexpr float threshold = 2.f;
    if ( fabs(deltaSize.x) < threshold && fabs(deltaSize.y) < threshold)
    {
        m_view.setSize(m_target_size);
        m_is_updating_size = false;
    }
    else
        // math
        m_view.setSize({ m_view.getSize().x + fabsf( deltaSize.x / 5.f) * (deltaSize.x > 0 ? 1.f : -1.f ),
                         m_view.getSize().y + fabsf( deltaSize.y / 5.f) * (deltaSize.y > 0 ? 1.f : -1.f )
        });

    // Update Grid after changing view
    GridSpace::updateGrid();
}



void Camera::updateCenter() {

}


void Camera::setCenterTarget(const sf::Vector2f & center_) {
    m_target_center = center_;
}

void Camera::setSizeTarget(const sf::Vector2f & size_) {
    m_target_size = size_;
}

sf::View & Camera::getView() {
    return m_view;
}

void Camera::moveCenterTarget(const sf::Vector2f & center_) {
    m_target_center += center_;
}

void Camera::moveSizeTarget(float&& size_) {
    m_target_size += { size_, size_ };
}

inline
constexpr float Camera::clamp(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

void Camera::updateStatus(Status s_, bool&& b_) {
    switch (s_) {
        case Status::Size:
            m_is_updating_size  = b_;
        case Status::Center:
            m_is_updating_scale = b_;
    }
}
