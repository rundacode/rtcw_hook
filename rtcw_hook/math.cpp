#include "math.h"
#include "globals.h"
#include <math.h>

namespace math
{
	void add(vec3_t a, vec3_t b, vec3_t out)
	{
		out[0] = a[0] + b[0];
		out[1] = a[1] + b[1];
		out[2] = a[2] + b[2];
	}

	void sub(vec3_t a, vec3_t b, vec3_t out)
	{
		out[0] = a[0] - b[0];
		out[1] = a[1] - b[1];
		out[2] = a[2] - b[2];
	}

	void mul(vec3_t a, float multiplier)
	{
		a[0] *= multiplier;
		a[1] *= multiplier;
		a[2] *= multiplier;
	}

	void angle_vectors(vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
	{
		float angle;
		static float sr, sp, sy, cr, cp, cy;

		angle = QDEG2RAD(angles[QPITCH]);
		sp = sinf(angle);
		cp = cosf(angle);

		angle = QDEG2RAD(angles[QYAW]);
		sy = sinf(angle);
		cy = cosf(angle);

		angle = QDEG2RAD(angles[QROLL]);
		sr = sinf(angle);
		cr = cosf(angle);

		if (forward)
		{
			forward[0] = cp * cy;
			forward[1] = cp * sy;
			forward[2] = -sp;
		}

		if (right)
		{
			right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
			right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
			right[2] = -1 * sr * cp;
		}

		if (up)
		{
			up[0] = (cr * sp * cy + -sr * -sy);
			up[1] = (cr * sp * sy + -sr * cy);
			up[2] = cr * cp;
		}
	}

	void vec_to_angle(const vec3_t vec, vec3_t &angles)
	{
		float	forward;
		float	yaw, pitch;

		if (vec[1] == 0 && vec[0] == 0)
		{
			yaw = 0;

			if (vec[2] > 0)
			{
				pitch = 90;
			}
			else
			{
				pitch = 270;
			}
		}
		else
		{
			if (vec[0])
				yaw = (atan2f(vec[1], vec[0]) * (180.0f / M_PI));
			else if (vec[1] > 0)
				yaw = 90.0f;
			else
				yaw = 270.0f;

			if (yaw < 0.0f)
				yaw += 360.0f;

			forward = sqrtf(vec[0] * vec[0] + vec[1] * vec[1]);
			pitch = (atan2f(vec[2], forward) * 180 / Q_PI);

			if (pitch < 0)
			{
				pitch += 360;
			}
		}

		angles[0] = -pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	void vec_to_viewangle(vec3_t vec, float* out)
	{
		vec3_t delta, angles;
		sub(vec, global::cg->refdef.vieworg, delta);
		vec_to_angle(delta, angles);

		if (angles[1] > 180.0f)
			angles[1] -= 360.0f;
		else if (angles[1] < -180.0f)
			angles[1] += 360.0f;

		if (angles[0] > 180.0f)
			angles[0] -= 360.0f;
		else if (angles[0] < -180.0f)
			angles[0] += 360.0f;

		angles[0] -= global::cg->refdefViewAngles[0];

		if (angles[0] > 180.0f)
			angles[0] -= 360.0f;
		else if (angles[0] < -180.0f)
			angles[0] += 360.0f;

		if (angles[1] > 180.0f)
			angles[1] -= 360.0f;
		else if (angles[1] < -180.0f)
			angles[1] += 360.0f;

		angles[1] -= global::cg->refdefViewAngles[1];

		out[0] = angles[0];
		out[1] = angles[1];
		out[2] = angles[2] = 0.f;
	}

	vec_t distance(vec3_t start, vec3_t end)
	{
		vec3_t v_length{};
		sub(end, start, v_length);
		return length(v_length);
	}

	vec_t length(const vec3_t vec)
	{
		return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	}

	vec_t normalize_360(float angle)
	{
		return (360.0f / 65536) * (static_cast<int>(angle * (65536 / 360.0f)) & 65535);
	}
}