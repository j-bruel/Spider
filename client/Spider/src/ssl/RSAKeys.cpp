//!
//! \file RSAKeys.cpp
//! \author jbruel
//! \date 26/09/2017
//!

#include <openssl/pem.h>
#include <memory>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include "ssl/RSAKeys.hpp"

namespace Spider
{
namespace ssl
{
		RSAKeys::RSAKeys(const std::string &pathPrivateKey, const std::string pathPublicKey)
		{
			readPrivateKey(pathPrivateKey);
			readPublicKey(pathPublicKey);
		}

		RSAKeys::~RSAKeys()
		{
			if (!mPrivate)
				RSA_free(mPrivate);
			if (!mPublic)
				RSA_free(mPublic);
			if (!mRsa)
				RSA_free(mRsa);
		}

		void RSAKeys::generate()
		{
			if (!mRsa)
				RSA_free(mRsa);
			//        mRsa = RSA_generate_key_ex(mBits, mExp, 0, 0);
			mRsa = RSA_generate_key(mBits, mExp, 0, 0);
		}

		bool RSAKeys::readPublicKey(const std::string &path)
		{
			FILE *fp;

			if ((fopen_s(&fp, path.c_str(), "r+")) != 0)
				return (false);
			if (mPublic)
				RSA_free(mPublic);
			if ((mPublic = PEM_read_RSA_PUBKEY(fp, &mPublic, nullptr, nullptr)) == nullptr)
				return (false);
			fclose(fp);
			return (true);
		}

		bool RSAKeys::readPrivateKey(const std::string &path)
		{
			FILE *fp;

			if ((fopen_s(&fp, path.c_str(), "r+")) != 0)
				if (mPrivate)
					RSA_free(mPrivate);
			if ((mPrivate = PEM_read_RSAPrivateKey(fp, nullptr, nullptr, nullptr)) == nullptr)
				return (false);
			fclose(fp);
			return (true);

		}

		void RSAKeys::write(FILE *publicKey, FILE *privateKey)
		{
			if (mRsa) {
				PEM_write_RSAPublicKey(publicKey, mRsa);
				PEM_write_RSAPrivateKey(privateKey, mRsa, nullptr, 0, 0, nullptr, nullptr);
				return;
			}
			if (mPrivate)
				PEM_write_RSAPrivateKey(privateKey, mPrivate, nullptr, 0, 0, nullptr, nullptr);
			if (mPublic)
				PEM_write_RSAPublicKey(publicKey, mPublic);
		}

		void RSAKeys::convertPrivate(std::string &pubKey, std::string &privKey)
		{
			FILE *publicTmp;
			FILE *privateTmp;

			fopen_s(&publicTmp, "public_tmp.pem", "w+");
			fopen_s(&privateTmp, "private_tmp.pem", "w+");
			write(publicTmp, privateTmp);
			fclose(publicTmp);
			fclose(privateTmp);

			boost::filesystem::ifstream ifsPub("public_tmp.pem");
			boost::filesystem::ifstream ifsPriv("private_tmp.pem");

			if (!ifsPub.is_open() || !ifsPriv.is_open())
				return;

			std::string buffPub((std::istreambuf_iterator<char>(ifsPub)), std::istreambuf_iterator<char>());
			std::string buffPriv((std::istreambuf_iterator<char>(ifsPriv)), std::istreambuf_iterator<char>());

			pubKey = buffPub;
			privKey = buffPriv;
			ifsPub.close();
			ifsPriv.close();
			std::remove("public_tmp.pem");
			std::remove("private_tmp.pem");
		}

		unsigned char *RSAKeys::encryptPublic(unsigned char *data, const size_t &clearLenght, int &cryptedLenght) const
		{
			unsigned char *encrypted = new unsigned char[RSA_size((this->mRsa == nullptr) ? mPublic : this->mRsa) + 1];

			if (mPublic == nullptr && mRsa == nullptr)
				return (nullptr);
			cryptedLenght = RSA_public_encrypt(clearLenght, (unsigned char *) "d"/*data*/, encrypted,
											   (mRsa == nullptr) ? mPublic : mRsa, RSA_PKCS1_PADDING);
			return (encrypted);
		}

		unsigned char *RSAKeys::encryptPrivate(unsigned char *data, const size_t &clearLenght, int &cryptedLenght) const
		{
			unsigned char *encrypted = new unsigned char[RSA_size((mRsa == nullptr) ? mPrivate : mRsa) + 1];

			if (mPublic == nullptr && mRsa == nullptr)
				return (nullptr);
			cryptedLenght = RSA_private_encrypt(clearLenght, data, encrypted, (mRsa == nullptr) ? mPrivate : mRsa,
												RSA_PKCS1_PADDING);
			return (encrypted);
		}

		unsigned char *RSAKeys::decryptPublic(unsigned char *data, size_t lenght) const
		{
			unsigned char *decrypted = new unsigned char[RSA_size((mRsa == nullptr) ? mPublic : mRsa) + 1];
			int idx;

			if (mPublic == nullptr && mRsa == nullptr)
				return (nullptr);
			idx = RSA_public_decrypt(lenght, data, decrypted, (mRsa == nullptr) ? mPublic : mRsa, RSA_PKCS1_PADDING);
			if (idx > 0)
				decrypted[idx] = '\0';
			return (decrypted);
		}

		unsigned char *RSAKeys::decryptPrivate(unsigned char *data, size_t lenght) const
		{
			unsigned char *decrypted = new unsigned char[RSA_size((mRsa == nullptr) ? mPrivate : mRsa) + 1];
			int idx = 0;

			if (mPublic == nullptr && mRsa == nullptr)
				return (nullptr);
			idx = RSA_private_decrypt(lenght, data, decrypted, (mRsa == nullptr) ? mPrivate : mRsa, RSA_PKCS1_PADDING);
			if (idx > 0)
				decrypted[idx] = '\0';
			for (int i = 0; i != idx; ++i)
				std::cout << decrypted[i] << std::endl;
			return (decrypted);
		}
	}
}