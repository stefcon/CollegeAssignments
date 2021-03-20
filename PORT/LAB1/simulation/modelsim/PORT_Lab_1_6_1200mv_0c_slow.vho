-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 13.1.0 Build 162 10/23/2013 SJ Web Edition"

-- DATE "06/28/2020 14:57:51"

-- 
-- Device: Altera EP3C16F484C6 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIII;
LIBRARY IEEE;
USE CYCLONEIII.CYCLONEIII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	PORT_Lab_1 IS
    PORT (
	a : OUT std_logic;
	SW3 : IN std_logic;
	SW2 : IN std_logic;
	SW1 : IN std_logic;
	SW0 : IN std_logic;
	b : OUT std_logic;
	d : OUT std_logic;
	c : OUT std_logic;
	e : OUT std_logic;
	f : OUT std_logic;
	g : OUT std_logic
	);
END PORT_Lab_1;

-- Design Ports Information
-- a	=>  Location: PIN_E11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b	=>  Location: PIN_F11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- d	=>  Location: PIN_H13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c	=>  Location: PIN_H12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- e	=>  Location: PIN_G12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f	=>  Location: PIN_F12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- g	=>  Location: PIN_F13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW2	=>  Location: PIN_H6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW0	=>  Location: PIN_J6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW3	=>  Location: PIN_G4,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW1	=>  Location: PIN_H5,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF PORT_Lab_1 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_a : std_logic;
SIGNAL ww_SW3 : std_logic;
SIGNAL ww_SW2 : std_logic;
SIGNAL ww_SW1 : std_logic;
SIGNAL ww_SW0 : std_logic;
SIGNAL ww_b : std_logic;
SIGNAL ww_d : std_logic;
SIGNAL ww_c : std_logic;
SIGNAL ww_e : std_logic;
SIGNAL ww_f : std_logic;
SIGNAL ww_g : std_logic;
SIGNAL \a~output_o\ : std_logic;
SIGNAL \b~output_o\ : std_logic;
SIGNAL \d~output_o\ : std_logic;
SIGNAL \c~output_o\ : std_logic;
SIGNAL \e~output_o\ : std_logic;
SIGNAL \f~output_o\ : std_logic;
SIGNAL \g~output_o\ : std_logic;
SIGNAL \SW2~input_o\ : std_logic;
SIGNAL \SW0~input_o\ : std_logic;
SIGNAL \SW3~input_o\ : std_logic;
SIGNAL \SW1~input_o\ : std_logic;
SIGNAL \inst~0_combout\ : std_logic;
SIGNAL \inst10~0_combout\ : std_logic;
SIGNAL \inst11~combout\ : std_logic;
SIGNAL \inst14~0_combout\ : std_logic;
SIGNAL \inst18~0_combout\ : std_logic;
SIGNAL \inst22~0_combout\ : std_logic;
SIGNAL \inst24~combout\ : std_logic;

BEGIN

a <= ww_a;
ww_SW3 <= SW3;
ww_SW2 <= SW2;
ww_SW1 <= SW1;
ww_SW0 <= SW0;
b <= ww_b;
d <= ww_d;
c <= ww_c;
e <= ww_e;
f <= ww_f;
g <= ww_g;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

-- Location: IOOBUF_X21_Y29_N23
\a~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst~0_combout\,
	devoe => ww_devoe,
	o => \a~output_o\);

-- Location: IOOBUF_X21_Y29_N30
\b~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst10~0_combout\,
	devoe => ww_devoe,
	o => \b~output_o\);

-- Location: IOOBUF_X28_Y29_N30
\d~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst11~combout\,
	devoe => ww_devoe,
	o => \d~output_o\);

-- Location: IOOBUF_X26_Y29_N2
\c~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst14~0_combout\,
	devoe => ww_devoe,
	o => \c~output_o\);

-- Location: IOOBUF_X26_Y29_N9
\e~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst18~0_combout\,
	devoe => ww_devoe,
	o => \e~output_o\);

-- Location: IOOBUF_X28_Y29_N23
\f~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst22~0_combout\,
	devoe => ww_devoe,
	o => \f~output_o\);

-- Location: IOOBUF_X26_Y29_N16
\g~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst24~combout\,
	devoe => ww_devoe,
	o => \g~output_o\);

-- Location: IOIBUF_X0_Y25_N22
\SW2~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW2,
	o => \SW2~input_o\);

-- Location: IOIBUF_X0_Y24_N1
\SW0~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW0,
	o => \SW0~input_o\);

-- Location: IOIBUF_X0_Y23_N8
\SW3~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW3,
	o => \SW3~input_o\);

-- Location: IOIBUF_X0_Y27_N1
\SW1~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW1,
	o => \SW1~input_o\);

-- Location: LCCOMB_X22_Y28_N0
\inst~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst~0_combout\ = (!\SW3~input_o\ & (!\SW1~input_o\ & (\SW2~input_o\ $ (\SW0~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst~0_combout\);

-- Location: LCCOMB_X22_Y28_N2
\inst10~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst10~0_combout\ = (\SW2~input_o\ & ((\SW3~input_o\) # (\SW0~input_o\ $ (\SW1~input_o\)))) # (!\SW2~input_o\ & (((\SW3~input_o\ & \SW1~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111001010101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst10~0_combout\);

-- Location: LCCOMB_X22_Y28_N12
inst11 : cycloneiii_lcell_comb
-- Equation(s):
-- \inst11~combout\ = (!\SW3~input_o\ & ((\SW2~input_o\ & (\SW0~input_o\ $ (!\SW1~input_o\))) # (!\SW2~input_o\ & (\SW0~input_o\ & !\SW1~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000100000000110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst11~combout\);

-- Location: LCCOMB_X22_Y28_N6
\inst14~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst14~0_combout\ = (\SW2~input_o\ & (((\SW3~input_o\)))) # (!\SW2~input_o\ & (\SW1~input_o\ & ((\SW3~input_o\) # (!\SW0~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst14~0_combout\);

-- Location: LCCOMB_X22_Y28_N8
\inst18~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst18~0_combout\ = (\SW1~input_o\ & (((\SW0~input_o\ & !\SW3~input_o\)))) # (!\SW1~input_o\ & ((\SW2~input_o\ & ((!\SW3~input_o\))) # (!\SW2~input_o\ & (\SW0~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110001001110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst18~0_combout\);

-- Location: LCCOMB_X22_Y28_N26
\inst22~0\ : cycloneiii_lcell_comb
-- Equation(s):
-- \inst22~0_combout\ = (!\SW3~input_o\ & ((\SW2~input_o\ & (\SW0~input_o\ & \SW1~input_o\)) # (!\SW2~input_o\ & ((\SW0~input_o\) # (\SW1~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000110100000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst22~0_combout\);

-- Location: LCCOMB_X22_Y28_N4
inst24 : cycloneiii_lcell_comb
-- Equation(s):
-- \inst24~combout\ = (!\SW3~input_o\ & ((\SW2~input_o\ & (\SW0~input_o\ & \SW1~input_o\)) # (!\SW2~input_o\ & ((!\SW1~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000100000000101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW2~input_o\,
	datab => \SW0~input_o\,
	datac => \SW3~input_o\,
	datad => \SW1~input_o\,
	combout => \inst24~combout\);

ww_a <= \a~output_o\;

ww_b <= \b~output_o\;

ww_d <= \d~output_o\;

ww_c <= \c~output_o\;

ww_e <= \e~output_o\;

ww_f <= \f~output_o\;

ww_g <= \g~output_o\;
END structure;


