require  Logger

Application.ensure_all_started(:httpoison)
Application.ensure_all_started(:timex)
dengta_url = "http://192.168.4.39:15600/api/services"
res = HTTPoison.get(dengta_url)
Logger.info "res:#{inspect res}"