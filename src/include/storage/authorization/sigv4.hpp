#pragma once

#include "storage/irc_authorization.hpp"
#include "aws.hpp"

namespace duckdb {

class SIGV4Authorization : public IRCAuthorization {
public:
	static constexpr const IRCAuthorizationType TYPE = IRCAuthorizationType::SIGV4;

public:
	SIGV4Authorization();
	SIGV4Authorization(const string &secret);

public:
	static unique_ptr<IRCAuthorization> FromAttachOptions(IcebergAttachOptions &input);
	unique_ptr<HTTPResponse> Request(RequestType request_type, ClientContext &context,
	                                 const IRCEndpointBuilder &endpoint_builder, HTTPHeaders &headers,
	                                 const string &data = "") override;

	void SetClient(unique_ptr<HTTPClient> && client_) {
		client = std::move(client_);
	}
	unique_ptr<HTTPClient> & GetClient() {
		return client;
	}
private:
	AWSInput CreateAWSInput(ClientContext &context, const IRCEndpointBuilder &endpoint_builder);

public:
	string secret;
	string region;
	unique_ptr<HTTPClient> client;
};

} // namespace duckdb
