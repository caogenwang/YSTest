defmodule Chain do
    require  Logger
    def counter(next_id) do
        receive do
            n ->
            send next_id,n+1
        end
    end

    def create_process(n) do
        last = Enum.reduce 1..n ,self(),
            fn (_,send_to) -> 
                spawn(Chain,:counter,[send_to])
            end

        send last,0

        receive do
            final_answer when is_integer(final_answer) ->
            "Result is #{inspect(final_answer)}"
        end
    end

    def run(n) do
        IO.puts inspect :timer.tc(Chain,:create_process,[n])
    end
end
# elixir -r chain.exs -e "Chain.run(100)"运行方法