//!
//! \file Sha.hpp
//! \author jbruel
//! \date 23/08/2017
//!

#ifndef IBS_FRAMEWORK_CORE_SHA_HPP
#define IBS_FRAMEWORK_CORE_SHA_HPP

#include <openssl/sha.h>
#include <cstdlib>
#include <cstring>

//!
//! \namespace Spider
//!
namespace Spider
{
//!
//! \namespace ssl
//!
namespace ssl
{
	//!
	//! \class Sha
	//! \brief Encapsulation of the openSSL one-way encryption system
	//!
	class Sha
	{
	public:
		//!
		//! \brief Default constructor
		//!
		Sha() = default;
		//!
		//! \brief Copy default constructor
		//!
		Sha(const Sha &) = delete;
		//!
		//! \brief Copy default overload equal operator
		//! \return Sha class
		//!
		Sha &operator=(const Sha &) = delete;
        //!
        //! \brief Default Destroyer
        //!
		~Sha() {}

	public:
		//!
		//! \brief Hash function
		//! \param data encrypted data
		//! \param size Size of the encrypted data
		//! \return Hash string
		//!
		static unsigned char    *hash(const char *data, int size = -1)
		{
			SHA256_CTX      ctx;
			unsigned char   *hash = new unsigned char[SHA256_DIGEST_LENGTH + 1];

			std::memset(hash, 0, SHA256_DIGEST_LENGTH);
			SHA256_Init(&ctx);
			if (size < 0)
				SHA256_Update(&ctx, data, std::strlen(data));
			else
				SHA256_Update(&ctx, data, size);
			SHA256_Final(hash, &ctx);
			return (hash);
		};
	};
}
};
#endif //IBS_FRAMEWORK_CORE_SHA_HPP
