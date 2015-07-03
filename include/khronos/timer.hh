#ifndef KHRONOS__TIMER__HH
#define KHRONOS__TIMER__HH

#include <functional>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace khronos
{
	class timer
	{
		public:
			using callback_t = std::function<bool(size_t, timer&)>;
			using duration_t = boost::posix_time::time_duration;

		public:
			timer(boost::asio::io_service& io,
			      const callback_t&        callback = callback_t(),
			      const duration_t&        duration = boost::posix_time::seconds(1),
			      bool                     enable   = true)
				: m_clock(io)
				, m_interval(duration)
				, m_callback(callback)
				, m_enabled(false)
				, m_count(0ul)
			{
				if (enable) start();
			}

			void start();
			void stop();
			void tick(const boost::system::error_code&);

			void              reset_count ()                                  { m_count = 0ul;         }
			size_t            get_count   ()                            const { return m_count;        }
			void              set_duration(const duration_t& duration)        { m_interval = duration; }
			const duration_t& get_duration()                            const { return m_interval;     }
			void              set_callback(const callback_t& callback)        { m_callback = callback; }
			const callback_t& get_callback()                            const { return m_callback;     }

		private:
			boost::asio::deadline_timer m_clock;
			duration_t                  m_interval;
			callback_t                  m_callback;
			bool                        m_enabled;
			size_t                      m_count;
	};
}

#endif
