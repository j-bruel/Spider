//!
//! \file AES.cpp
//! \author jbruel
//! \date 27/09/2017
//!

#include <cstring>
#include <cstdlib>
#include <io.h>  
#include "ssl/AES.hpp"

namespace Spider
{
namespace ssl
{
	AES::AES() { std::memset(mKey, 0, AES_BLOCK_SIZE); }

	AES::AES(const AES &key) { std::memcpy(mKey, key.mKey, AES_BLOCK_SIZE); }

	AES::AES(const unsigned char *key) { std::memcpy(mKey, key, AES_BLOCK_SIZE); }

	AES     &AES::operator=(const AES &key)
	{
		std::memcpy(mKey, key.mKey, AES_BLOCK_SIZE);
		return (*this);
	}

	unsigned char *AES::get()
	{
		unsigned char   *key = new unsigned char[AES_BLOCK_SIZE];

		std::memcpy(key, mKey, AES_BLOCK_SIZE);
		return (key);
	}

	bool 	AES::isInitialize() const
	{
		unsigned char	ref[AES_BLOCK_SIZE];

		std::memset(ref, 0, AES_BLOCK_SIZE);
		return (std::memcmp(mKey, ref, AES_BLOCK_SIZE) == 0 ? false : true);
	}

	void    AES::write(int fd)
	{
//		std::string key(Base64::encode((char *)mKey, AES_BLOCK_SIZE));

//		::_write(fd, key.c_str(), key.size());
	}

	std::string AES::crypt(const std::string &data) const
	{
		AES_KEY       enc_key;
		unsigned char *aes_input = new unsigned char[data.size() + 1];
		unsigned char aes_key[AES_BLOCK_SIZE];
		unsigned char iv[AES_BLOCK_SIZE];

		std::memset(iv, 0x00, AES_BLOCK_SIZE);
		std::memcpy(aes_input, data.c_str(), data.size() + 1);

		unsigned char *enc_out = new unsigned char[data.size()];

		std::memset(enc_out, '\0', data.size());
		memcpy(aes_key, mKey, AES_BLOCK_SIZE);
		AES_set_encrypt_key(aes_key, sizeof(aes_key)*8, &enc_key);
		AES_cbc_encrypt(aes_input, enc_out, data.size() , &enc_key, iv, AES_ENCRYPT);

//		size_t len = Base64::lenght((unsigned char *)data.c_str());
		delete aes_input;
//		return (std::string(Base64::encode((char *)enc_out, len)));
		return ("");
	}

	std::string AES::uncrypt(const std::string &data) const
	{
		AES_KEY       dec_key;
		unsigned char iv[AES_BLOCK_SIZE];
		unsigned char aes_key[AES_BLOCK_SIZE];
		unsigned char *aes_output = nullptr;
		size_t        aes_outputlen = 0;

//		if ((aes_output = Base64::decode(data, &aes_outputlen)) == 0)
//			return (0);
		unsigned char *enc_out = new unsigned char[aes_outputlen - 1];
		unsigned char *dec_out = new unsigned char[aes_outputlen - 1];

		std::memset(enc_out, '\0', aes_outputlen - 1);
		std::memset(dec_out, '\0', aes_outputlen - 1);
		std::memset(iv, 0x00, AES_BLOCK_SIZE);
		std::memcpy(aes_key, mKey, AES_BLOCK_SIZE);
		std::memcpy(enc_out, aes_output, (((aes_outputlen - 1)/16 + 1) * 16));
		AES_set_decrypt_key(aes_key, sizeof(aes_key) * 8, &dec_key);
		AES_cbc_encrypt(enc_out, dec_out, aes_outputlen - 1, &dec_key, iv, AES_DECRYPT);

		char          *out = new char[aes_outputlen + 1];

		std::memcpy(out, dec_out, aes_outputlen - 1);
		out[aes_outputlen - 1] = '\0';
		delete aes_output;

		std::string uncryptData(out);
		delete out;
		return (uncryptData);
	}
}
}