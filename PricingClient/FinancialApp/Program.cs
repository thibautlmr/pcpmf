using FinancialApp;
using ParameterInfo;
using PricingClient;

class Program
{
    static async Task Main(string[] args)
    { 
        string serverAddress = "http://localhost:50051";
        string[] argsMano = { "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\params\\test-param1.json", "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\params\\MarketData.csv" };
        Input input = new(argsMano);
        DataUtilities dataUtilities = new(input);
        double[] spots = dataUtilities.GetSpots(dataUtilities.MarketData[0].Date);
        List<List<double>> past = new() { spots.ToList() };
        List<DateTime> dates = dataUtilities.GetDateTimes(dataUtilities.MarketData);
        Pricer priceAndDeltaInfo = await GrpcClientUtil.GetPriceAndDeltasAsync(serverAddress, true, 0, past);
        if (priceAndDeltaInfo != null)
        {
            Console.WriteLine($"Price Call Vanille: {priceAndDeltaInfo.Price}");
        }
        ComputationUtilities computationUtilities = new(priceAndDeltaInfo, dataUtilities);
        List<DateTime> dateTimes = dataUtilities.GetDateTimes(dataUtilities.MarketData);
        var marketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dateTimes[0]);
        Handler handler = new(computationUtilities, marketDataCurrDate);
        //List<OutputData> outputDatas = new();

        for (int t = 1; t < dateTimes.Count; t++)
        {
            handler.MarketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dateTimes[t]);
            if (computationUtilities.RebalancingTime(t))
            {
                handler.GetPortfolioValue();
                handler.UpdateCompo();
                //handler.AddOutputData(outputDatas);
                handler.MarketDataPrevDate = dataUtilities.GetDataFeedForOneDate(dateTimes[t]);
            }
        }
        //File.WriteAllText(dataUtilities.Input.OutputFilePath, DataUtilities.GetJsonFromObject(outputDatas));
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }
}