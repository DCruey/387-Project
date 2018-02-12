----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:14:14 01/24/2018 
-- Design Name: 
-- Module Name:    Prog_2 - Behavioral 
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Prog_2 is
	 Generic ( DELAY : integer := 640000 -- DELAY = 20 mS / clk_period
				  );	
    Port ( Clk : in STD_LOGIC;
			  Switch : in  STD_LOGIC;
           LED : out  STD_LOGIC_VECTOR (7 downto 0));
end Prog_2;

architecture Behavioral of Prog_2 is

	COMPONENT debounce
	Generic ( DELAY : integer := 640000 -- DELAY = 20 mS / clk_period
				  );
	PORT(
		clk : IN std_logic;
		sig_in : IN std_logic;          
		sig_out : OUT std_logic
		);
	END COMPONENT;

signal Sec : STD_LOGIC_VECTOR(26 downto 0) := (others => '0');
signal Count1 : STD_LOGIC_VECTOR(3 downto 0) := "0000";
signal Count2 : STD_LOGIC_VECTOR(3 downto 0) := "0000";
signal Switch_deb : STD_LOGIC := '0';

begin

	debounce_run: debounce 
	GENERIC MAP(DELAY => DELAY)
	PORT MAP(
		clk => Clk ,
		sig_in => Switch,
		sig_out => Switch_deb 
	);

LED(7 downto 4) <= Count1;
LED(3 downto 0) <= Count2;

process(Clk)
begin
	if(rising_edge(Clk)) then
		if Sec /= "101111101011110000100000001" then
			Sec <= Sec + '1';
		else
			Sec <= (others => '0');
		end if;
	end if;
end process;

process(Clk)
begin
	if(rising_edge(Clk)) then
		if Sec = "101111101011110000100000001" then
			Count1 <= Count1 + '1';
		end if;
	end if;
end process;

process(Switch_deb)
begin
	if rising_edge(Switch_deb) then
			Count2 <= Count2 + '1';
	end if;
end process;

end Behavioral;

