#include "Time.h"

namespace Cpain {
	namespace CTime {

		void Time::tick() {
			clock::time_point now = clock::now();
			m_time = std::chrono::duration<float>(now - m_startTime).count();
			m_deltaTime = std::chrono::duration<float>(now - m_frameTime).count();
			m_frameTime = now;
		}

	}
}

