#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY),
	zoom(ZOOM)//��ʼ�������λ�á�����Ȳ���
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
	GLfloat upX, GLfloat upY, GLfloat upZ,
	GLfloat yaw, GLfloat pitch)
	: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY),
	zoom(ZOOM)
{
	this->position = glm::vec3(posX, posY, posZ);
	this->worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}
void Camera::processKeyboard(Camera_Movement direction, float deltaTime)//���̰����ص�
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)//����ƶ��ص�
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	updateCameraVectors();
}
void Camera::processMouseScroll(float yoffset)//���ֻص�
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}
glm::mat4 Camera::getViewMatrix()//�۲����
{
	return glm::lookAt(position, position + front, up);
}
void Camera::updateCameraVectors()//��������������λ��
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch)); 
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
