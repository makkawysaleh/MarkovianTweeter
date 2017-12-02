// A utility to encode a given string to base64
// Modified by Dikshant Adhikari
// Modified from https://github.com/gofer/libbase64
// Changes made to remove methods not used by this program

namespace Base64 {

    std::array<char, 64> Base64Table{{
                                             'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                             'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                             'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                             'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                             '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
                                     }};

    std::string _encode_split(std::string in) {
      in.resize(3, 0);

      char _out[5];
      _out[0] = Base64Table.at(static_cast<unsigned long>((in[0] & 0xFC) >> 2));
      _out[1] = Base64Table.at(static_cast<unsigned long>((in[0] & 0x03) << 4 | (in[1] & 0xF0) >> 4));
      _out[2] = Base64Table.at(static_cast<unsigned long>((in[1] & 0x0F) << 2 | (in[2] & 0xC0) >> 6));
      _out[3] = Base64Table.at(static_cast<unsigned long>(in[2] & 0x3F));
      _out[4] = '\0';

      return std::string(_out);
    }

    std::string encode(const std::string &src) {
      std::string dst;
      for (uint64_t i = 0; i < src.length(); i += 3) {
        dst = dst.append(_encode_split(src.substr(i, 3)));
      }

      switch (src.length() % 3) {
        case 0 :
          break;
        case 1 :
          dst.erase(dst.length() - 2, 2);
              dst.append("==");
              break;
        case 2 :
          dst.erase(dst.length() - 1, 1);
              dst.append("=");
              break;
          default:break;
      }
      return dst;
    }

};