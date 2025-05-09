// license:BSD-3-Clause
// copyright-holders:smf
#ifndef MAME_CPU_F2MC16_MB90640A_H
#define MAME_CPU_F2MC16_MB90640A_H

#pragma once

#include "f2mc16.h"
#include "f2mc16_clock.h"
#include "f2mc16_intc.h"
#include "f2mc16_port.h"
#include "f2mc16_ppg.h"
#include "f2mc16_reload.h"
#include "f2mc16_uart.h"

class mb90640a_device :
	public f2mc16_device
{
public:
	template<unsigned N> typename std::enable_if<N < 11, f2mc16_port_device>::type &port() const { if (m_port[N]) return *m_port[N]; return *subdevice<f2mc16_port_device>(m_port[N].finder_tag()); }
	auto &ppg() const { if (m_ppg) return *m_ppg; return *subdevice<f2mc16_ppg_device>(m_ppg.finder_tag()); }
	template<unsigned N> typename std::enable_if<N < 5, f2mc16_reload_timer_device>::type &reload_timer() const { if (m_reload_timer[N]) return *m_reload_timer[N]; return *subdevice<f2mc16_reload_timer_device>(m_reload_timer[N].finder_tag()); }
	template<unsigned N> typename std::enable_if<N < 2, f2mc16_uart_device>::type &uart() const { if (m_uart[N]) return *m_uart[N]; return *subdevice<f2mc16_uart_device>(m_uart[N].finder_tag()); }

protected:
	mb90640a_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device_t
	virtual void device_add_mconfig(machine_config &config) override ATTR_COLD;
	virtual space_config_vector memory_space_config() const override ATTR_COLD;

	void internal_map(address_map &map) ATTR_COLD;

	const address_space_config m_program_config;

	required_device<f2mc16_clock_generator_device> m_clock_generator;
	required_device<f2mc16_intc_device> m_intc;
	required_device_array<f2mc16_port_device, 11> m_port;
	required_device<f2mc16_ppg_device> m_ppg;
	required_device_array<f2mc16_reload_timer_device, 5> m_reload_timer;
	required_device_array<f2mc16_uart_device, 2> m_uart;
};

class mb90641a_device : public mb90640a_device
{
public:
	mb90641a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

DECLARE_DEVICE_TYPE(MB90641A, mb90641a_device)

#endif // MAME_CPU_F2MC16_MB90640A_H
