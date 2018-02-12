----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:22:16 01/24/2018 
-- Design Name: 
-- Module Name:    Prog - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Prog is
	port (Clk : in STD_LOGIC);
end Prog;

architecture Behavioral of Prog is

-- signal x1 : STD_LOGIC_VECTOR (3 downto 0) := "1100";
signal y : STD_LOGIC_VECTOR (3 downto 0) := "1010";
signal t : STD_LOGIC_VECTOR (3 downto 0) := "0000";

signal x : STD_LOGIC_VECTOR (3 downto 0) := "1100";


begin



process(Clk)
	begin
		if(rising_edge(clk)) then
			-- x <= x1;
			y <= x + "0010";
			t <= y;
			x <= t;
		end if;
end process;


end Behavioral;

