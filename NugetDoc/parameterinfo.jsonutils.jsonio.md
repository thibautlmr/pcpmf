# JsonIO

Namespace: ParameterInfo.JsonUtils

Helper class for conversions between [TestParameters](./parameterinfo.testparameters.md) objects and json strings.

```csharp
public static class JsonIO
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [JsonIO](./parameterinfo.jsonutils.jsonio.md)

## Methods

### **ToJson(TestParameters)**

Conversion of a [TestParameters](./parameterinfo.testparameters.md) object into a json string

```csharp
public static string ToJson(TestParameters testParams)
```

#### Parameters

`testParams` [TestParameters](./parameterinfo.testparameters.md)<br>
The object to convert

#### Returns

[String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>

### **ToJson(OutputData)**

Conversion of a [OutputData](./parameterinfo.outputdata.md) object into a json string

```csharp
public static string ToJson(OutputData outputData)
```

#### Parameters

`outputData` [OutputData](./parameterinfo.outputdata.md)<br>
The object to convert

#### Returns

[String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>

### **ToJson(List&lt;OutputData&gt;)**

Conversion of a list of [OutputData](./parameterinfo.outputdata.md) objects into a json string

```csharp
public static string ToJson(List<OutputData> outputDataList)
```

#### Parameters

`outputDataList` [List&lt;OutputData&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1)<br>
The list of objects to convert

#### Returns

[String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>

### **FromJson(String)**

Deserialization of a json string into a [TestParameters](./parameterinfo.testparameters.md) object.

```csharp
public static TestParameters FromJson(string jsonDescr)
```

#### Parameters

`jsonDescr` [String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>
Json string to deserialize.

#### Returns

[TestParameters](./parameterinfo.testparameters.md)<br>

#### Exceptions

[ArgumentNullException](https://docs.microsoft.com/en-us/dotnet/api/system.argumentnullexception)<br>
