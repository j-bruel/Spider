//!
//! \file AES.hpp
//! \author jbruel
//! \date 30/09/2017
//!

#ifndef IBS_SPIDER_SSL_AES_HPP
#define IBS_SPIDER_SSL_AES_HPP

#include <string>
#include <cstring>
#include <openssl/rand.h>
#include <openssl/aes.h>

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
	//! \class AES
	//! \brief Encapsulation of the openSSL AES system
	//! \warning The AES key to a size defined by the openSSl (AES_BLOCK_SIZE)
	//!
	class   AES
	{
	private:
		unsigned char   mKey[AES_BLOCK_SIZE]; //!< Key in the form of characters

	public:
		//!
		//! \brief Default AES Class Constructor
		//!
		AES();
		//!
		//! \brief AES class copy constructor
		//! \param key Key that will be copied
		//!
		AES(const AES &key);
		//!
		//! \brief Constructor that automatically loads a key from its path and is type
		//! \param key Key in the form of a string
		//!
		AES(const unsigned char *key);
		//!
		//! \brief Copy Operator, copy a key
		//! \param key Reference key (to be copied)
		//! \return Instance of class AES
		//!
		AES     &operator=(const AES &key);
        //!
        //! \brief Equal operator, allows to know if two keys are equal
        //! \param key Reference key (to be copied)
        //! \return State of the method: Success or Failure
        //!
        inline bool    operator==(const AES &key) const { return ((std::memcmp(mKey, key.mKey, AES_BLOCK_SIZE)) == 0 ? true : false); }
        //!
		//! \brief Default Destroyer
		//!
		~AES() {}

	public:
		//!
		//! \brief Generates a new internal key of the class
		//! \return State of the method: Success or Failure
		//!
		inline void   	generate() {RAND_bytes(mKey, AES_BLOCK_SIZE);}
		//!
		//! \brief Assigns a key to the instance
		//! \param key Reference key to be used
		//!
		inline void   	affect(const unsigned char *key) {std::memcpy(mKey, key, AES_BLOCK_SIZE);}
        //!
        //! \brief Removes the key without destroying the object
        //!
        inline void     clear() {std::memset(mKey, 0, AES_BLOCK_SIZE);}
        //!
        //! \brief Whether the key is initialized or not
        //! \return State of the method: Success or Failure
        //!
		bool 			isInitialize() const;

	public:
		//!
		//! \brief Extract the key from the class
		//! \return Key in the form of a string
		//!
		unsigned char *get();

	public:
		//!
		//! \brief Read AES key in a file
		//! \param path Path for the file
		//! \return State of the method: Success or Failure
		//!
		bool    read(const std::string &path);
		//!
		//! \brief Write the key in a specific file director
		//! \param fd File Director to write in
		//!
		void    write(int fd);

	public:
		//!
		//! \brief Encrypts data from a class key
		//! \param data Data to encrypt
		//! \return Data encrypted
		//!
		std::string crypt(const std::string &data) const;
		//!
		//! \brief Decrypts data from class AESKey
		//! \param data Data to uncrypt
		//! \return Clear data
		//!
		std::string uncrypt(const std::string &data) const;
	};
}
}

#endif //IBS_SPIDER_SSL_AES_HPP
