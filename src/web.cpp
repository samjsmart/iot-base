#include "web.h"

String page(String title, String content) {
  return
  "<!DOCTYPE html>\n"
  "<html lang=\"en\">\n"
  "<head>\n"
    "<meta charset=\"utf-8\">\n"
    "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    "<title>" + title + "</title>\n"
    "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">\n"
    "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\">\n"
  "</head>\n"
  "<body>\n"
    "<div style=\"margin:0 auto;max-width:900px;text-align:center;\">" + content + "</div>\n"
  "</body>\n"
  "</html>";
}
