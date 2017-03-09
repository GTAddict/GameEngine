template <typename T>
Datum* Attributed::AddPrescribedAttributeInternal(const std::string& name, const T& data)
{
	return AddPrescribedAttributeInternal(name, &data, 1);
}

template <typename T>
Datum* Attributed::AddPrescribedAttributeInternal(const std::string& name, const T* data, const std::uint32_t size)
{
	THROW_IF_NULL(data);

	// Already added, return
	if (IsAttribute(name))
	{
		return nullptr;
	}

	Datum& datum = Append(name);

	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*(data + i), i);
	}

	s_mPrescribedAttributes[TypeIdClass()][name] = datum;

	return &datum;
}

template <typename T>
Datum* Attributed::AddPrescribedAttributeExternal(const std::string& name, const T& data)
{
	return AddPrescribedAttributeExternal(name, &data, 1);
}

template <typename T>
Datum* Attributed::AddPrescribedAttributeExternal(const std::string& name, const T* data, const std::uint32_t size)
{
	THROW_IF_NULL(data);

	// Already added, return
	if (IsAttribute(name))
	{
		return nullptr;
	}

	Datum& datum = Append(name);
	datum.SetStorage(data, size);

	s_mPrescribedAttributes[TypeIdClass()][name] = datum;

	return &datum;
}