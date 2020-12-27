#pragma once
#include "q3types.h"

#define	QPITCH		0
#define	QYAW		1	
#define	QROLL		2
#define QX			0
#define QY			1
#define QZ			2
#define	Q_PI		3.14159265358979323846f

#define QDEG2RAD( degree )		( ( ( degree ) * Q_PI ) / 180.0f )
#define QRAD2DEG( radian )		( ( ( radian ) * 180.0f ) / Q_PI )

namespace math
{
	void	add(vec3_t a, vec3_t b, vec3_t out);
	void	sub(vec3_t a, vec3_t b, vec3_t out);
	void	mul(vec3_t a, float multiplier);

	void	vec_to_viewangle(vec3_t vec, float* out);
	void	vec_to_angle(const vec3_t vec, vec3_t& angles);
	void	angle_vectors(vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
	vec_t	distance(vec3_t start, vec3_t end);
	vec_t	length(const vec3_t vec);
	vec_t	normalize_360(float angle);
}