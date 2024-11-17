-- library IEEE;
-- use IEEE.STD_LOGIC_1164.ALL;
-- use IEEE.STD_LOGIC_ARITH.ALL;
-- use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- library work;
-- use work.array_t.all;

-- entity fir_sol is
--     Port ( 
--         Reset : in  STD_LOGIC;
--         Clk : in  STD_LOGIC;
--         Input : in array32_t(0 to 9); -- This data type is defined in components/array_t.vhd
--         Output : out  STD_LOGIC_VECTOR (31 downto 0)
--   );
-- end fir_sol;

-- architecture Behavioral of fir_sol is
--     component adder 
--     Port ( A : in  STD_LOGIC_VECTOR (31 downto 0);
--            B : in  STD_LOGIC_VECTOR (31 downto 0);
--            O : out  STD_LOGIC_VECTOR (31 downto 0));
--     end component;

--     component reg 
--     Port ( Reset : in  STD_LOGIC;
--            Clk : in  STD_LOGIC;
--            Load : in  STD_LOGIC;
--            Din : in  STD_LOGIC_VECTOR (31 downto 0);
--            Dout : out  STD_LOGIC_VECTOR (31 downto 0));
--     end component;

--     component mul32_32 
--     Port ( A : in  STD_LOGIC_VECTOR (31 downto 0);
--            B : in  STD_LOGIC_VECTOR (31 downto 0);
--            O : out  STD_LOGIC_VECTOR (31 downto 0));
--     end component;

--     signal mult_out : STD_LOGIC_VECTOR (31 downto 0) := (others => '0');
--     signal add_out : STD_LOGIC_VECTOR (31 downto 0) := (others => '0');
--     signal reg_out : STD_LOGIC_VECTOR (31 downto 0) := (others => '0');
--     signal index : integer range 0 to 9 := 0;
--     signal done : STD_LOGIC := '0';
--     signal load : STD_LOGIC := '0';
--     signal input_a : STD_LOGIC_VECTOR (31 downto 0) := (others => '0');
--     signal input_b : STD_LOGIC_VECTOR (31 downto 0) := (others => '0');
    
-- begin
--     process(Clk, Reset)
--     begin
--         if Reset = '1' then
--             index <= 0;
--             done <=  '0';
--             load <= '0';


--         elsif rising_edge(Clk) then
--             if done = '0' then
--                 input_a <= Input(index);
--                 input_b <= fir_const(index);
--                 load <= '1';
                
--                 if index = 9 then
--                     done <= '1';
--                 else
--                     index <= index + 1;
--                 end if;
--             else
--                 load <= '0';
--             end if;
--         end if;
--     end process;

--     reg_inst: reg
--         port map (
--             Reset => Reset,
--             Clk => Clk,
--             Load => load,
--             Din => mult_out,
--             Dout => reg_out
--         );

--     mul_inst: mul32_32
--         port map (
--             A => input_a,
--             B => input_b,
--             O => mult_out
--         );

--     add_inst: adder
--         port map (
--             A => reg_out,
--             B => mult_out,
--             O => add_out
--         );


--     Output <= add_out;  
-- end Behavioral;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

library work;
use work.array_t.all;

entity fir_base is
    Port ( 
        Reset : in  STD_LOGIC;
        Clk : in  STD_LOGIC;
        Input : in array32_t(0 to 9);
        Output : out  STD_LOGIC_VECTOR (31 downto 0)
    );
end fir_base;

architecture Behavioral of fir_base is

    -- We declare the multiplier and adder components only once
    component adder 
    Port ( A : in  STD_LOGIC_VECTOR (31 downto 0);
           B : in  STD_LOGIC_VECTOR (31 downto 0);
           O : out  STD_LOGIC_VECTOR (31 downto 0));
    end component;

    component mul32_32 
    Port ( A : in  STD_LOGIC_VECTOR (31 downto 0);
           B : in  STD_LOGIC_VECTOR (31 downto 0);
           O : out  STD_LOGIC_VECTOR (31 downto 0));
    end component;

    -- Signals to hold the intermediate values of multiplication and addition
    signal mout : array32_t(0 to 9); -- Store multiplication results
    signal aout : array32_t(0 to 8); -- Store intermediate sums

    -- Accumulation signal (used for partial sums)
    signal acc : STD_LOGIC_VECTOR(31 downto 0) := (others => '0');

begin

    -- Step 1: Multiplication by constants
    -- Loop through the input array and multiply by constants
    f1: for i in 0 to 9 generate
        mul: mul32_32 port map (
            A => Input(i),
            B => fir_const(i), -- Assuming `fir_const` is a predefined constant array
            O => mout(i)
        );
    end generate f1;

    -- Step 2: Accumulate the results using a single adder to reduce area
    process(Clk)
    begin
        if rising_edge(Clk) then
            -- Initialize accumulation result to zero at the beginning
            if Reset = '1' then
                acc <= (others => '0');
            else
                -- Accumulate the multiplications using the same adder
                -- Start with the first multiplication result
                acc <= mout(0);
                for i in 1 to 9 loop
                    acc <= acc + mout(i);  -- Accumulate the values
                end loop;
            end if;
        end if;
    end process;

    -- The output is the final accumulated value
    Output <= acc;

end Behavioral;
