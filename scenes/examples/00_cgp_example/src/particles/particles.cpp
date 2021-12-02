#include "particles.hpp"

using namespace cgp;



particle_bubble::particle_bubble(float creation_time)
{
	t0 = creation_time;
	float const theta = rand_interval(0.0f, 2 * Pi);
	float const radius_position = rand_interval(0.0f, 0.7f);
	p0 = radius_position * vec3(std::cos(theta), 0.25f, std::sin(theta));
	radius = rand_interval(0.03f, 0.08f);
	color = { 0.5f + rand_interval(0,0.2f),0.6f + rand_interval(0,0.2f),1.0f - rand_interval(0,0.2f) };
}

vec3 particle_bubble::evaluate_position(float absolute_time) const
{
	float const t = absolute_time - t0;

#ifdef SOLUTION
	float const x = 0.15f * std::cos(t * 5);
	float const z = 0.15f * std::sin(t * 5);
	float const y = (10 - radius) / 7.0f * t;
	return vec3{ x,y,z } + p0;
#else
	// To be modified ...
	return { std::sin(3 * t), t, 0.0f };
#endif

}

particle_billboard::particle_billboard(float creation_time)
{
	t0 = creation_time;
#ifdef SOLUTION
	float const theta = rand_interval(0.0f, 2 * Pi);
	p0 = 0.5f * vec3(std::cos(theta), 0.0f, std::sin(theta)) + vec3(0, 0.25f, 0);
#else
	// To be completed ...
#endif
}

vec3 particle_billboard::evaluate_position(float absolute_time) const
{
#ifdef SOLUTION
	float const t = absolute_time - t0;

	float const theta = std::atan2(p0.x, p0.z);
	float const x = t / 2 * std::sin(theta);
	float const z = t / 2 * std::cos(theta);
	float const y = -5 * (t / 3) * (t / 3) + 2.5f * (t / 3);

	return p0 + vec3(x, y, z);
#else
	// To be modified
	return { 0,0,0 };
#endif

}


template <typename T>
static void remove_old_element(std::vector<T>& container, float current_time, float max_time)
{
	// Loop over all active particles
	for (auto it = container.begin(); it != container.end();)
	{
		// if a particle is too old, remove it
		if (current_time - it->t0 > max_time)
			it = container.erase(it);

		// Go to the next particle if we are not already on the last one
		if (it != container.end())
			++it;
	}
}


void particle_system_structure::remove_old_particles(float t)
{
	remove_old_element(bubbles, t, 3.0f);
	remove_old_element(billboards, t, 3.0f);
}