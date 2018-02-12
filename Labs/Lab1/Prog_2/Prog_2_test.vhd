--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   15:02:25 01/24/2018
-- Design Name:   
-- Module Name:   C:/Users/James/Documents/College Semesters/8 Spring 2018/Junior Design/Lab1/Prog_2/Prog_2_test.vhd
-- Project Name:  Prog_2
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Prog_2
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY Prog_2_test IS
END Prog_2_test;
 
ARCHITECTURE behavior OF Prog_2_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Prog_2
    PORT(
         Clk : IN  std_logic;
         Switch : IN  std_logic;
         LEDs : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal Clk : std_logic := '0';
   signal Switch : std_logic := '0';

 	--Outputs
   signal LEDs : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant Clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Prog_2 PORT MAP (
          Clk => Clk,
          Switch => Switch,
          LEDs => LEDs
        );

   -- Clock process definitions
   Clk_process :process
   begin
		Clk <= '0';
		wait for Clk_period/2;
		Clk <= '1';
		wait for Clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	
		Switch <= '1';
		
		wait for 100 ns;	
		Switch <= '0';
		
		wait for 100 ns;	
		Switch <= '1';
		
		wait for 1000 ns;	
		Switch <= '0';
		
		wait for 1000 ns;	
		Switch <= '1';
		
		wait for 1000 ns;	
		Switch <= '0';
		
		wait for 1000 ns;	
		Switch <= '1';

		wait for 1000 ns;	
		Switch <= '0';
		
		wait for 1000 ns;	
		Switch <= '1';

      wait for Clk_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
