//!
//! \file RSAKeys.hpp
//! \author jbruel
//! \date 26/09/2017
//!

#pragma once

#include <string>
#include <openssl\rsa.h>

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
	//! \class RSAKeys
	//! \brief Encapsulation of the openSSL one-way encryption system
	//!
	class RSAKeys
	{
	private:
		const int mBits = 1024; //!< Number bytes
		const int mExp = 3; //! Exp informations for RSA crypto

	private:
		RSA     *mPublic; //! Public RSA key
		RSA     *mPrivate; //! Private RSA key
		RSA     *mRsa; //! RSA envelop keys

	public:
		//!
		//! \brief Default constructor
		//!
		RSAKeys() : mPublic(nullptr), mPrivate(nullptr), mRsa(nullptr) {}
		//!
		//! \brief Copy constructor
		//!
		RSAKeys(const RSAKeys &) = delete;
		//!
		//! \brief Create RSA keys with the two keys path
		//! \param pathPrivateKey Path to the private key
		//! \param pathPublicKey Path to the public key
		//!
		RSAKeys(const std::string &pathPrivateKey, const std::string pathPublicKey);
		//!
		//! \brief Equal operator overload
		//! \return RSA keys
		//!
		RSAKeys  &operator=(const RSAKeys &) = delete;
		//!
		//! \brief Default Destroyer
		//!
		~RSAKeys();

	public:
		//!
		//! \brief Generate two keys (private and public)
		//!
		void        generate();
		//!
		//! \brief Extract the private key from the RSAKeys envelop
		//! \return OpenSSL RSA type
		//!
		inline RSA  *getPrivate() const { return (mPrivate); }
		//!
		//! \brief Extract the public key from the RSAKeys envelop
		//! \return OpenSSL RSA type
		//!
		inline RSA  *getPublic() const { return (mPublic); }

	public:
		//!
		//! \brief Read and extract a public key from a file
		//! \param path Key path
		//! \return Status function
		//!
		bool   readPublicKey(const std::string &path);
		//!
		//! \brief Read and extract a private key from a file
		//! \param path Key path
		//! \return Status function
		//!
		bool   readPrivateKey(const std::string &path);

	public:
		//!
		//! \brief Print on stdout the public and private key
		//! \param publicKey FILE type to Public Key
		//! \param privateKey FILE type to Private Key
		//!
		void    write(FILE *publicKey, FILE *privateKey);
		//!
		//! \brief Convert the Private and public key into strings
		//! \param pubKey Ouput public key
		//! \param privKey Ouput private key
		//!
		void	RSAKeys::convertPrivate(std::string &pubKey, std::string &privKey);

	public:
		//!
		//! \brief Encrypt data from a public key
		//! \param data Data to encrypt
		//! \param lenght Lenght of the data
		//! \return Encrypted data
		//!
		unsigned char   *encryptPublic(unsigned char *data, const size_t &clearLenght, int &cryptedLenght) const;
		//!
		//! \brief Encrypt data from a private key
		//! \param data Data to encrypt
		//! \param lenght Lenght of the data
		//! \return Encrypted data
		//!
		unsigned char   *encryptPrivate(unsigned char *data, const size_t &clearLenght, int &cryptedLenght) const;
		//!
		//! \brief Decrypt data from a public key
		//! \param data Data to decrypt
		//! \param lenght Lenght of the data
		//! \return Decrypted data
		//!
		unsigned char   *decryptPublic(unsigned char *data, size_t lenght) const;
		//!
		//! \brief Decrypt data from a private key
		//! \param data Data to decrypt
		//! \param lenght Lenght of the data
		//! \return Decrypted data
		//!
		unsigned char   *decryptPrivate(unsigned char *data, size_t lenght) const;
	};
}
}