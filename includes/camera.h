#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <vector>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 12.5f;
const float SENSITIVITY = 0.1f;
const float HEIGHT = 1024;
const float WIDTH = 720;

class Camera
{
public:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mRight;
    glm::vec3 mUp;
    glm::vec3 mWorldUp;

    float mYaw;
    float mPitch;
    float mMovementSpeed;
    float mMouseSensitivity;
    float mAspectRatio;
    float mNearZ, mFarZ;

    glm::mat4 mProjView;
    glm::mat4 mView;
    glm::mat4 mProj;

    Camera() {};

    void Init(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH, float aspectRatio = HEIGHT / WIDTH, float nearZ = 0.1f, float farZ = 100.0f)
    {
        mFront = glm::vec3(0.0f, 0.0f, -1.0f);
        mMovementSpeed = SPEED;
        mMouseSensitivity = SENSITIVITY;
        mPosition = position;
        mWorldUp = up;
        mYaw = yaw;
        mPitch = pitch;
        mAspectRatio = aspectRatio;
        mNearZ = nearZ;
        mFarZ = farZ;

        mProj = glm::perspective(glm::radians(45.0f), mAspectRatio, mNearZ, mFarZ);
        updateCameraValues();
    }

    void Init(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch,
        float aspectRatio = HEIGHT / WIDTH, float nearZ = 0.1f, float farZ = 100.0f)
    {
        mFront = glm::vec3(0.0f, 0.0f, -1.0f);
        mMovementSpeed = SPEED;
        mMouseSensitivity = SENSITIVITY;
        mPosition = glm::vec3(posX, posY, posZ);
        mWorldUp = glm::vec3(upX, upY, upZ);
        mYaw = yaw;
        mPitch = pitch;
        mAspectRatio = aspectRatio;
        mNearZ = nearZ;
        mFarZ = farZ;

        mProj = glm::perspective(glm::radians(45.0f), mAspectRatio, mNearZ, mFarZ);
        updateCameraValues();
    }

    void setProjectionMatrix(float aspectRatio, float nearZ, float farZ)
    {
        mAspectRatio = aspectRatio;
        mNearZ = nearZ;
        mFarZ = farZ;
        mProj = glm::perspective(glm::radians(45.0f), mAspectRatio, mNearZ, mFarZ);
        updateCameraValues();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(mPosition, mPosition + mFront, mUp);
    }

    glm::mat4 GetProjMatrix()
    {
        return mProj;
    }

    glm::mat4 GetProjViewMatrix()
    {
        return mProjView;
    }

    void ProcessKeyboard(CameraMovement direction, float deltaTime)
    {
        float distance = mMovementSpeed*deltaTime;
        if (direction == FORWARD)
            mPosition += mFront*distance;
        if (direction == BACKWARD)
            mPosition -= mFront*distance;
        if (direction == LEFT)
            mPosition -= mRight*distance;
        if (direction == RIGHT)
            mPosition += mRight*distance;

        updateCameraValues();
    }

    void move(float xOffset, float yOffset, bool constrainPitch = true)
    {
        xOffset *= mMouseSensitivity;
        yOffset *= mMouseSensitivity;

        mYaw += xOffset;
        mPitch += yOffset;

        if (constrainPitch) {
            if (mPitch > 89.0f)
                mPitch = 89.0f;
            if (mPitch < -89.0f)
                mPitch = -89.0f;
        }

        updateCameraValues();
    }

private:
    void updateCameraValues()
    {
        float x, y, z, w, u, v;
        x = glm::radians(mPitch);
        y = glm::radians(mYaw);
        z = cos(glm::radians(mPitch));
        w = cos(glm::radians(mYaw));
        u = sin(glm::radians(mPitch));
        v = sin(glm::radians(mYaw));

        glm::vec3 tempFront;
        tempFront.x = cos(glm::radians(mPitch))*cos(glm::radians(mYaw));
        tempFront.y = sin(glm::radians(mPitch));
        tempFront.z = sin(glm::radians(mYaw))*cos(glm::radians(mPitch));

        mFront = glm::normalize(tempFront);

        mRight = glm::normalize(glm::cross(mFront, mWorldUp));
        mUp = glm::normalize(glm::cross(mRight, mFront));

        glm::vec3 temp = mPosition + mFront;
        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjView = mProj*mView;
        return;
    }
};

#endif