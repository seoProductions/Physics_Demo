
#include "Camera.hpp"
#include "GridSpace.hpp"

Camera::Camera() {
    m_target_size = m_view.getSize();
    m_is_updating_size  = false;
    m_is_updating_center = false;
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
    if ( fabsf(deltaSize.x) < threshold && fabsf(deltaSize.y) < threshold)
    {
        m_view.setSize(m_target_size);
        m_is_updating_size = false;
    }
    else
        // math
        m_view.setSize({ m_view.getSize().x + fabsf( deltaSize.x / 8.f) * (deltaSize.x > 0 ? 1.f : -1.f ),
                         m_view.getSize().y + fabsf( deltaSize.y / 8.f) * (deltaSize.y > 0 ? 1.f : -1.f )
        });

    // Update Grid after changing view
    GridSpace::updateGrid();
}


void Camera::updateCenter() {
    if (!m_is_updating_center)                  return;
    if (m_target_center == m_view.getCenter())  return;
    if (Time::getDeltaTime() > 1)           // for intense lag
    {
        m_view.setCenter(m_target_center);
        return;
    }

    m_target_center.x = clamp(m_target_center.x, m_min_center.x, m_max_center.x);
    m_target_center.y = clamp(m_target_center.y, m_min_center.y, m_max_center.y);

    // quick check for negligible difference
    const auto deltaCenter = m_target_center - m_view.getCenter();

    constexpr float threshold = 1.f;
    if ( fabsf(deltaCenter.x) < threshold && fabsf(deltaCenter.y) < threshold)
    {
        m_view.setCenter(m_target_center);
        m_is_updating_center = false;
    }
    else
        // math
        m_view.setCenter({  m_view.getCenter().x + fabsf( deltaCenter.x / 15.f) * (deltaCenter.x > 0 ? 1.f : -1.f ),
                            m_view.getCenter().y + fabsf( deltaCenter.y / 15.f) * (deltaCenter.y > 0 ? 1.f : -1.f )
                            });

    // Update Grid after changing view
    GridSpace::updateGrid();
}


void Camera::setCenterTarget(const sf::Vector2f & center_) {
    m_target_center = center_;
    m_is_updating_center = true;
}

void Camera::setSizeTarget(const sf::Vector2f & size_) {
    m_target_size = size_;
    m_is_updating_size = true;
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
            m_is_updating_center = b_;
    }
}
