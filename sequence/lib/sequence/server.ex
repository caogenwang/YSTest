defmodule Sequence.Server do
    use GenServer
    def handle_call(:next_num,_from,current_number) do
        {:replay,current_number,current_number+1}
    end
end