#include "Camera.hpp"

namespace gps {


    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));
        //TODO - Update the rest of camera parameters

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        if (direction == MOVE_FORWARD) {
            glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
            cameraPosition += speed * cameraFront;
            cameraTarget += speed * cameraFront;
        }
        if (direction == MOVE_BACKWARD) {
            glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
            cameraPosition -= speed * cameraFront;
            cameraTarget -= speed * cameraFront;
        }
        if (direction == MOVE_LEFT) {
            glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUpDirection, cameraTarget - cameraPosition));
            cameraPosition += speed * cameraRight;
            cameraTarget += speed * cameraRight;
        }
        if (direction == MOVE_RIGHT) {
            glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUpDirection, cameraTarget - cameraPosition));
            cameraPosition -= speed * cameraRight;
            cameraTarget -= speed * cameraRight;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        // Calculați noile unghiuri de rotație
        // pitch - rotația în jurul axei X (sus/jos)
        // yaw - rotația în jurul axei Y (stânga/dreapta)

        // Limitați unghiurile de pitch pentru a evita inversarea camerei
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        // Conversia unghiurilor în radiani
        float pitchRadian = glm::radians(pitch);
        float yawRadian = glm::radians(yaw);

        // Calculați noile direcții pentru camera
        glm::vec3 front;
        front.x = cos(yawRadian) * cos(pitchRadian);
        front.y = sin(pitchRadian);
        front.z = sin(yawRadian) * cos(pitchRadian);

        // Actualizați direcția camerei și ținta camerei
        this->cameraFrontDirection = glm::normalize(front);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
        this->cameraTarget = cameraPosition + cameraFrontDirection;
    }
}