using FinancialApp;
using GrpcPricing.Protos;
using ParameterInfo;

class Program
{
    static async Task Main(string[] args)
    { 
        string serverAddress = "http://localhost:50051";
        string[] argsMano = { "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\params\\test-param1.json", "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\params\\MarketData.csv" };
        Input input = new(argsMano);
        DataUtilities dataUtilities = new(input);
        List<DateTime> dates = dataUtilities.GetDateTimes(dataUtilities.MarketData);
        ComputationUtilities computationUtilities = new(null, dataUtilities);
        PricingInputUtilities pricingInputUtilities = new(dataUtilities);
        PricingInput pricingInput = pricingInputUtilities.CreatePricingInput();
/*        var priceAndDeltaInfo = await GrpcClientUtil.GetPriceAndDeltasAsync(serverAddress, pricingInput);
        if (priceAndDeltaInfo != null)
        {
            Console.WriteLine($"Price Call Vanille: {priceAndDeltaInfo.Price}");
        }*/

        List<DateTime> dateTimes = dataUtilities.GetDateTimes(dataUtilities.MarketData);
        var marketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dateTimes[0]);
        Handler handler = new(computationUtilities, marketDataCurrDate);
        List<OutputData> outputDatas = new();

        for (int t = 1; t < dateTimes.Count; t++)
        {
            handler.MarketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dateTimes[t]);
            if (computationUtilities.RebalancingTime(t))
            {
                handler.GetPortfolioValue();
                handler.UpdateCompo();
                handler.AddOutputData(outputDatas);
                handler.MarketDataPrevDate = dataUtilities.GetDataFeedForOneDate(dateTimes[t]);
            }
        }
        //File.WriteAllText(dataUtilities.Input.OutputFilePath, DataUtilities.GetJsonFromObject(outputDatas));
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }
}