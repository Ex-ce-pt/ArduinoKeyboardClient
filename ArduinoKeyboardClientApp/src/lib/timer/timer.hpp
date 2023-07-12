#pragma once

#include <chrono>
#include <functional>
#include <map>

#include "math/hashing.hpp"

using namespace std::chrono_literals;

namespace shared::util {
	struct timer_info {
		std::uint32_t									m_id{};
		std::chrono::high_resolution_clock::time_point	m_start_time{};
		std::chrono::milliseconds						m_delay{};
		std::function<void()>							m_action{};
		bool											m_self_destruct{};
	};

	class c_timer_mgr {
		std::vector<uint32_t>							m_active_timers{};
		std::map<uint32_t, timer_info>					m_registered_timers{};
		std::chrono::high_resolution_clock::time_point	m_current_time{};

		bool											m_running = true;
	public:
		c_timer_mgr() {
			std::thread([=] { update_timers(); }).detach();
		}

		~c_timer_mgr() {
			m_running = false;
		}

		void create_timer(std::string timer_name, std::chrono::milliseconds delay, std::function<void()> action, bool self_destruct) {
			timer_info _info = { shared::math::fnv(timer_name.c_str()), std::chrono::high_resolution_clock::now(), delay, action, self_destruct };
			create_timer(shared::math::fnv(timer_name.c_str()), _info);
		}

		void delete_timer(std::string timer_name) {
			delete_timer(shared::math::fnv(timer_name.c_str()));
		}

	private:
		void update_timers() {
			while (m_running) {
				m_current_time = std::chrono::high_resolution_clock::now();

				for (std::uint32_t active_timer_it : m_active_timers) {
					std::chrono::milliseconds time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(m_current_time - m_registered_timers[active_timer_it].m_start_time);

					if (!m_registered_timers[active_timer_it].m_action)
						continue;

					if (time_elapsed < m_registered_timers[active_timer_it].m_delay)
						continue;

					m_registered_timers[active_timer_it].m_action();
					m_registered_timers[active_timer_it].m_start_time = m_current_time;

					if (!m_registered_timers[active_timer_it].m_self_destruct)
						continue;

					delete_timer(m_registered_timers[active_timer_it].m_id);
				}
			}
		}

		void create_timer(std::uint32_t timer_hash, timer_info info) {
			m_registered_timers[timer_hash] = info;
			m_active_timers.push_back(timer_hash);
		}

		void delete_timer(std::uint32_t timer_hash) {
			for (unsigned int ix = 0; ix < m_active_timers.size(); ix++) {
				if (timer_hash != m_active_timers[ix])
					continue;

				std::vector<uint32_t>::iterator it = m_active_timers.begin();
				std::advance(it, ix);

				m_registered_timers.erase(ix);
				m_active_timers.erase(it);
			}
		}
	};
}
