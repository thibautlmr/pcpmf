# ShareValueGenerator

Namespace: MarketDataGeneration

Class that permits to generate market data, either as a list or in a csv file

```csharp
public static class ShareValueGenerator
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [ShareValueGenerator](./marketdatageneration.sharevaluegenerator.md)

## Methods

### **Create(TestParameters, MarketInfo)**

Generation of market data as a list

```csharp
public static List<ShareValue> Create(TestParameters tstParams, MarketInfo mktInfo)
```

#### Parameters

`tstParams` [TestParameters](./parameterinfo.testparameters.md)<br>
The parameters describing the assets available in the market

`mktInfo` [MarketInfo](./marketdatageneration.marketinfo.md)<br>
The information on trends and initial spots

#### Returns

[List&lt;ShareValue&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1)<br>
The list of share values

### **Create(TestParameters, MarketInfo, String)**

Generation of market data that is stored in a csv file

```csharp
public static void Create(TestParameters tstParams, MarketInfo mktInfo, string filename)
```

#### Parameters

`tstParams` [TestParameters](./parameterinfo.testparameters.md)<br>
The parameters describing the assets available in the market

`mktInfo` [MarketInfo](./marketdatageneration.marketinfo.md)<br>
The information on trends and initial spots

`filename` [String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>
