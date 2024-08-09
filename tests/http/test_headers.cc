#include <gtest/gtest.h>
#include <sstream>

extern "C" {
#include <etch.h>
}


TEST(HTTPHeadersTest, TestHeaderToString)
{
        EtchHeader header = etch_header_new("Content-Length", "100");
        char *str = etch_header_to_string(header);

        ASSERT_STREQ(str, "Content-Length: 100\r\n");
        etch_header_free(header);
}

TEST(HTTPHeadersTest, TestHeadersToString)
{
        EtchHeader *headers = (EtchHeader*) malloc(sizeof(EtchHeader) * 4);
        headers[0] = etch_header_new("Connection", "close");
        headers[1] = etch_header_new("Content-Type", "text/html; charset=utf-8");
        headers[2] = etch_header_new("Content-Language", "en-US");
        headers[3] = etch_header_new("X-Test-Header", "hewo there");

        const char* body = "123456789";

        char *headers_str = etch_headers_to_string(headers, 4, body);

        std::stringstream ss{};
        ss << "Content-Length: 9\r\n"
           << "Connection: close\r\n"
           << "Content-Type: text/html; charset=utf-8\r\n"
           << "Content-Language: en-US\r\n"
           << "X-Test-Header: hewo there\r\n"
           << "\r\n";

        ASSERT_STREQ(ss.str().c_str(), headers_str);
        etch_headers_free(headers, 4);
}

// TODO write tests for "etch_header_from_string"

// TEST(HTTPHeadersTest, TestStringToHeader) {
//     // Test the case where the buffer ends
//     const char* str = "Content-Type: text/html; charset=utf-8\r\n\r\nHello, World";

//     EtchHeader header;
//     etch_header_from_string(str, EtchHeader *header)
// }