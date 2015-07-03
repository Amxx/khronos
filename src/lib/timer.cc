#include <khronos/timer.hh>

void khronos::Timer::start()
{
	if (!m_enabled)
	{
		m_enabled = true;
		m_clock.expires_from_now(m_interval);
		m_clock.async_wait(std::bind(&khronos::Timer::tick, this, std::placeholders::_1));
	}
}

void khronos::Timer::stop()
{
	if (m_enabled)
	{
		m_enabled = false;
		m_clock.cancel();
	}
}

void khronos::Timer::tick(const boost::system::error_code& ec)
{
	if (!ec && m_enabled)
	{
		if (!m_callback || m_callback(++m_count, *this))
		{
			m_clock.expires_at(m_clock.expires_at() + m_interval);
			m_clock.async_wait(std::bind(&khronos::Timer::tick, this, std::placeholders::_1));
		}
		else
			m_enabled = false;
	}
}