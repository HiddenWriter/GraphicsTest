#pragma once
class DXGIInfoManager
{
public:
	DXGIInfoManager();
	~DXGIInfoManager() = default;
	DXGIInfoManager(const DXGIInfoManager&) = delete;
	DXGIInfoManager& operator=(const DXGIInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;

private:
	unsigned long long mNext = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> mpDxgiInfoQueue;
};

