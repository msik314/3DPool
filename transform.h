#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0))
	{
		m_pos = pos;
		m_rot = rot;
		m_scale = scale;
	}

	inline glm::mat4 getModel() const
	{
		glm::mat4 posMat = glm::translate(m_pos);
		glm::mat4 rotMat = glm::rotate(glm::angle(m_rot), glm::axis(m_rot));
		glm::mat4 scaleMat = glm::scale(m_scale);

		return posMat * rotMat * scaleMat;
	}

	inline glm::vec3& getPos() { return m_pos; }
	inline glm::quat& getRot() { return m_rot; }
	inline glm::vec3& getScale() { return m_scale; }
	inline const glm::vec3& getPos() const { return m_pos; }
	inline const glm::quat& getRot() const { return m_rot; }
	inline const glm::vec3& getScale() const { return m_scale; }

private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;
};


#endif
