----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:07:55 01/31/2018 
-- Design Name: 
-- Module Name:    PWM - Behavioral 
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PWM is
    Port ( clk : in STD_LOGIC;
			  switches : in  STD_LOGIC_VECTOR (7 downto 0);
           InO : out  STD_LOGIC);
			  
end PWM;

architecture Behavioral of PWM is

signal count : STD_LOGIC_VECTOR (7 downto 0) := "00000000";

begin

	process(clk, count)
	begin
		if rising_edge(clk) then
			count <= count + '1';
		end if;
	end process;
		
	process(count, switches)
	begin
		if (count < switches) then
			InO <= '1';
		else
			InO <= '0';
		end if;
	end process;
	

end Behavioral;

